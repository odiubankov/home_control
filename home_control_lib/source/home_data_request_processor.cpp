//
// Copyright(c) 2018 Oleksii Diubankov
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#include "home_data_request_processor.h"
#include "ihome_data_provider.h"

namespace hctrl {

HomeDataRequestProcessor::HomeDataRequestProcessor(std::unique_ptr<IHomeDataProvider> homeDataProvider)
    : RequestProcessor("HomeData")
    , homeDataProvider_( std::move(homeDataProvider) )
{}

//HomeDataRequestProcessor::~HomeDataRequestProcessor() = default;
//HomeDataRequestProcessor::HomeDataRequestProcessor(HomeDataRequestProcessor&&) = default;
//HomeDataRequestProcessor& HomeDataRequestProcessor::operator=(HomeDataRequestProcessor&&) = default;


std::string HomeDataRequestProcessor::process() const
{
    return homeDataProvider_->getHomeDataJson();
}

}
