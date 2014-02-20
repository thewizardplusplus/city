#include "EmptyMessageException.h"

using namespace thewizardplusplus::city_client::exceptions;

EmptyMessageException::EmptyMessageException(void) :
	CityClientException("not allowed send an empty message")
{}
