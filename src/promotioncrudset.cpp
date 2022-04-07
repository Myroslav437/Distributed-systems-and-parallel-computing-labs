#include "../include/promotioncrudset.h"

void PromotionCrudSet::Get(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            auto data = Dbcontroller::GetInstance()->getPromotions();
            int arridx = 0;
            for(const auto& a : data) {
                auto tmpval = JsonConverter::promotionToJson(a.second);
                tmpval["id"] = a.first;
                jval[arridx++] = tmpval;
            }
        }
        else if((it = queries.find("id")) != queries.end()) {
            auto data = Dbcontroller::GetInstance()->getPromotion(std::stoi(it->second));
            auto tmpval = JsonConverter::promotionToJson(data.second);
            tmpval["id"] = data.first;

            jval[0] = tmpval;
        }
        else if (it == queries.end()){
            throw std::invalid_argument("Invalid query");
        }

        message.reply(web::http::status_codes::OK, jval).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
    catch(const std::exception& e) {
        message.reply(web::http::status_codes::BadRequest, e.what(),  U("text/plain")).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
}

void PromotionCrudSet::Post(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

void PromotionCrudSet::Put(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

void PromotionCrudSet::Delete(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}