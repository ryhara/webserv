#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <ctime>
#include <sys/stat.h>
#include <cstdio>

#include "Webserv.hpp"
#include "HTTPStatusCode.hpp"
#include "HTTPRequest.hpp"

#define DATE_BUF_SIZE 128
#define DATE_FORMAT "%a, %d %b %Y %H:%M:%S GMT"

class HTTPResponse
{
	private:
		std::string _version;
		HTTPStatusCode _statusCode;
		std::string _statusMessage;
		std::string _statusLine;
		bool keepAlive;
		size_t _contentLength;
		std::map<std::string, std::string> _headers;
		std::string _body;
		std::map<HTTPStatusCode, std::string> _statusMessageMap;
		std::string _responseMessage;
		DISALLOW_COPY_AND_ASSIGN(HTTPResponse);
	public :
		HTTPResponse();
		~HTTPResponse();

		// setter
		void setVersion(const std::string &version);
		void setStatusCode(const HTTPStatusCode &statusCode);
		void setStatusMessage(const std::string &statusMessage);
		void setStatusLine(void);
		void setKeepAlive(const bool &keepAlive);
		void setContentLength(const size_t &contentLength);
		void setHeader(const std::string &key, const std::string &value);
		void setBody(const std::string &body);
		void setBodyAll(void);
		void setStatusMessageMap(void);
		// getter
		const std::string &getVersion() const;
		const HTTPStatusCode &getStatusCode() const;
		const std::string &getStatusMessage() const;
		const std::string &getStatusLine() const;
		const bool &getKeepAlive() const;
		const size_t &getContentLength() const;
		const std::map<std::string, std::string> &getHeaders() const;
		const std::string &getBody() const;
		const std::string &getStatusMessageFromMap(const HTTPStatusCode &statusCode) const;
		const std::string &getResponseMessage() const;


		void selectResponse(HTTPRequest &request);
		void handleNormalRequest(HTTPRequest &request);
		void handleCGIRequest(HTTPRequest &request);
		void handleAutoIndexRequest(HTTPRequest &request);
		void handleRedirectRequest(HTTPRequest &request);
		void handleErrorResponse(HTTPRequest &request);

		std::string makeResponseMessage(HTTPRequest &request);
		void makeFileBody(const std::string &path);
		void makeGetResponseBody(HTTPRequest &request);
		void makePostResponseBody(HTTPRequest &request);
		void makeDeleteResponseBody(HTTPRequest &request);
		std::string makeResponseStatusLine(void);

		std::string getDateTimestamp(void) const;
		std::string getTimeStampForPost(void) const;
		bool isFileExist(const std::string &path, struct stat *stat);
		bool isDirectory(struct stat &stat);
		bool isFile(struct stat &stat);

};

/* response example */
// HTTP/1.1 200 OK
// Connection: keep-alive
// Content-Length: 192
// Date: Thu, 21 Dec 2023 02:01:21 GMT
// Server: webserv/1.0.0

// <!DOCTYPE html>
// <html>

// <head>
//   <meta charset='utf-8'>
//   <title>Welcome to webserv!</title>
// </head>

// <body>
//   <h1>Welcome to webserv!</h1>
//   <p>Hello from docs/index.html</p>
// </body>