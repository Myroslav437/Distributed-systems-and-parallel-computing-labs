#include <atomic>
#include <chrono>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace param 
{
    // namespace contains the arguments values;
    enum class Modes 
    {
        Generative,
        Calculate,
        //Help,
    };

    std::string filename;
    Modes currentMode = Modes::Calculate;
    int pointsToGenerate = 100;
    int threadsCount = 1;
}

struct point3 {
    double x;
    double y;
    double m;
};

void setCurrentMode(const param::Modes& m);
void setPointsToGenerate(const std::string& str);
void setThreadsCount(const std::string& str);
void setFileName(const std::string& str);
void runMPoint();
void generatePoints(int count, const std::string& dest);
void calculateMPoint(int threads, const std::string& src);

std::atomic<int> finishedThreads(0);

int main(int argc, char *argv[]) 
{
    // Check the amount of arguments:
    if(argc < 2) {
        std::cout << "Invalid amount of arguments" << std::endl;
        return 1; 
    }

    // Parse the input arguments
    for(int i = 1; i < argc - 1; i++) {
        std::string val(argv[i]);

        try {
            if(val == "-g") {           // Generative mode:
                setCurrentMode(param::Modes::Generative);
            }
            else if(val == "-c") {      // Amount of points:
                if(++i >= argc - 1) {
                    throw std::invalid_argument("Invalid argument value -c: expecting an integer");
                }
                setPointsToGenerate(argv[i]);
            }
            else if (val == "-t") {     // Amount of threads:
                if(++i >= argc - 1) {
                    throw std::invalid_argument("Invalid argument value -t: expecting an integer");
                }
                setThreadsCount(argv[i]);
            }
        }
        catch(const std::exception& e) {
            std::cout << "Error while parsing the input arguments: " << e.what() << std::endl;
            return 1;
        }
    }

    // Get the filename:
    try{
        setFileName(argv[argc - 1]);
    }
    catch(const std::exception& e) {
        std::cout << "Error: invalid filename: " << e.what() << std::endl;
        return 1;
    }

    // Run the program:
    try{
        runMPoint();
    }
    catch(std::exception& e) {
        std::cout << "Error occured while executing the program: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


void setCurrentMode(const param::Modes& m)
{
    param::currentMode = m;
}

void setPointsToGenerate(const std::string& str) 
{
    try {
        param::pointsToGenerate = std::stoi(str);
        if( param::pointsToGenerate <= 0) {
            throw std::invalid_argument("");
        }
    }
    catch(const std::exception& e) {
        param::pointsToGenerate = 100;
        throw std::invalid_argument("Invalid <Points to generate> value - should be a positive integer\n" + std::string(e.what()));
    }
}

void setThreadsCount(const std::string& str) 
{
    try {
        param::threadsCount = std::stoi(str);
        if( param::threadsCount <= 0) {
            throw std::invalid_argument("");
        }
    }
    catch(const std::exception& e) {
        param::threadsCount = 1;
        throw std::invalid_argument("Invalid <Threads count> value - should be a positive integer\n" + std::string(e.what()));
    }
}

void setFileName(const std::string& str) 
{
    param::filename = str;
}

void runMPoint()
{
    if(param::currentMode == param::Modes::Generative) {
        generatePoints(param::pointsToGenerate, param::filename);
    }
    else if (param::currentMode == param::Modes::Calculate) {
        calculateMPoint(param::threadsCount, param::filename);
    }
}

void generatePoints(int count, const std::string& dest) 
{
    std::ofstream ofs(dest);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 10.0);

    if(!ofs.is_open()) {
        throw std::runtime_error("Cannot create the " + dest + " file");
    }

    for(int i = 0; i < count; ++i) {
        ofs << distribution(generator) << ", "<< distribution(generator) << ", " << distribution(generator) << std::endl; // [x, y, m];
    }

    ofs.close();
    std::cout << "Successfully generated " << count << " points into " << dest << std::endl;
}

std::vector<point3> parseFile(const std::string& src){
    std::ifstream ifs(src);
    if(!ifs.is_open()) {
        throw std::runtime_error("Cannot open the " + src + " file");
    }

    std::vector<point3> res;
    std::string line;

    try {
        while(std::getline(ifs,line)) {
            std::stringstream ss(line);
            
            std::string xstr, ystr, mstr;
            std::getline(ss, xstr,',');
            std::getline(ss, ystr,',');
            std::getline(ss, mstr,',');

            double x = std::stod(xstr);
            double y = std::stod(ystr);
            double m = std::stod(mstr);

            res.emplace_back(point3{x, y, m});
        }
    }
    catch(const std::exception& e) {
        throw std::runtime_error("Error while parsing the file");
    }

    return res;
}

void runThread(int id, int threads, std::vector<point3>& vec) 
{
    // if(id == 0) {
    //     int dbg = 0;
    //     dbg++;
    // }
    // if(id == 1) {
    //     int dbg = 0;
    //     dbg++;
    // }
    // if(id == 2) {
    //     int dbg = 0;
    //     dbg++;
    // }

    const auto N = vec.size();
    for(int i = 0; i < N / threads; ++i) {
        int p2idx = N - threads * (i + 1) + id;
        if(p2idx < threads) {
            break;
        }

        point3 p1 = vec[id];
        point3 p2 = vec[p2idx];
        vec[id].x = (p1.x*p1.m + p2.x*p2.m) / (p1.m + p2.m);
        vec[id].y = (p1.y*p1.m + p2.y*p2.m) / (p1.m + p2.m);
        vec[id].m = p1.m + p2.m;
    }

    finishedThreads.fetch_add(1, std::memory_order::memory_order_seq_cst);
}

void calculateMPoint(int threads, const std::string& src) 
{
    std::vector<point3> points = parseFile(src);
    point3 res;

    auto start = std::chrono::steady_clock::now();

    for(int i = 0; i < threads; ++i) {
        std::thread([=, &points]{runThread(i, threads, points);}).detach();
    }

    // wait for all threads to finish
    while (finishedThreads.load(std::memory_order_seq_cst) != threads);

    // sum up:
    double x = 0, y = 0, m = 0;
    for(int i = 0; i < threads; ++i) {
        x += points[i].x * points[i].m;
        y += points[i].y * points[i].m;
        m += points[i].m;
    }
    res = point3{x/m, y/m, m };

    auto end = std::chrono::steady_clock::now();

    // output results:
    std::cout << "Result: " << "{" << res.x << ", " << res.y << "}" << "    m = " << res.m << std::endl; 
    std::cout << "Elapsed time: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " microseconds" << std::endl;
}