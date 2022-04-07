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
    try{
        const auto data = message.content_ready().get().extract_vector().get();
        const utility::string_t body = { data.begin(), data.end() };

        web::json::value jval = web::json::value::parse(body);
        if(!jval.is_null()) {
            int jsize = jval.size();
            for(int i = 0; i < jsize; ++i) {
                auto promotion = JsonConverter::JsonToPromotion(jval[i]);
                Dbcontroller::GetInstance()->addPromotion(promotion);
            }

            message.reply(web::http::status_codes::OK,  U("text/plain")).then([](pplx::task<void> t)
            {
                try { t.get(); }
                catch(...) { }
            });
        }
        else{
            throw std::invalid_argument("Invalid JSON string");
        }
    }
    catch(const std::exception& e) {
        message.reply(web::http::status_codes::BadRequest, e.what(),  U("text/plain")).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
}

void PromotionCrudSet::Put(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            throw std::invalid_argument("Invalid query");
        }
        else if((it = queries.find("id")) != queries.end()) {
            auto val = Dbcontroller::GetInstance()->getPromotion(std::stoi(it->second));
            // <promotionDescription, promotionValidFrom, promotionValidUntill>:
            if((it = queries.find("promotionDescription")) != queries.end()) {
                std::get<0>(val.second.get()) = it->second;
            }
            if((it = queries.find("promotionValidFrom")) != queries.end()) {
                std::get<1>(val.second.get()) = it->second;
            }
            if((it = queries.find("promotionValidUntill")) != queries.end()) {
                std::get<2>(val.second.get()) = it->second;
            }
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

void PromotionCrudSet::Delete(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            throw std::invalid_argument("Invalid query");
        }
        else if((it = queries.find("id")) != queries.end()) {
            Dbcontroller::GetInstance()->removePromotion(std::stoi(it->second));
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