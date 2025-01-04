enum class API_HEADER {
	UNDEFINED,
	GET_CREDITS
};

struct Request {
	API_HEADER header{API_HEADER::UNDEFINED};

};

struct Response {
	API_HEADER header{API_HEADER::UNDEFINED};
};

struct CreditsResponse : Response {
	int value{0};
};