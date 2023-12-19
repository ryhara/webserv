#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include "../srcs/server/HTTPRequestParse.hpp"

char example[] = "GET /cgi/index.html HTTP/1.1\r\nHost: localhost:4242\r\nConnection: keep-alive\r\nsec-ch-ua: \"Not_A Brand\";v=\"8\", \"Chromium\";v=\"120\", \"Google Chrome\";v=\"120\"\r\n";

TEST(HTTPRequestParseTest, readRequestLineTest) {
	HTTPRequest request;
	HTTPRequestParse parse(request);
	std::string line = "GET / HTTP/1.1";
	parse.readRequestLine(line);
	EXPECT_EQ(request.getMethod(), "GET");
	EXPECT_EQ(request.getUri(), "/");
	EXPECT_EQ(request.getVersion(), "HTTP/1.1");
}

TEST(HTTPRequestParseTest, readHeadersTest) {
	char example1[] = "Host: localhost:4242\r\nConnection: keep-alive\r\n";
	HTTPRequest request;
	HTTPRequestParse parse(request);
	std::stringstream ss(example1);
	parse.readHeaders(ss);
	EXPECT_EQ(request.getHeaders()["Host"], "localhost:4242");
	EXPECT_EQ(request.getHeaders()["Connection"], "keep-alive");
}

TEST(HTTPRequestParseTest, parseTest1) {
	char example2[] = "GET / HTTP/1.1\r\nHost: localhost:4242\r\nConnection: keep-alive\r\n";
	HTTPRequest request;
	HTTPRequestParse parse(request);
	parse.parse(example2);
	EXPECT_EQ(request.getMethod(), "GET");
	EXPECT_EQ(request.getUri(), "/");
	EXPECT_EQ(request.getVersion(), "HTTP/1.1");
	// TODO : その他の変数のテストも追加
}

TEST(HTTPRequestParseTest, parseTest2) {
	HTTPRequest request;
	HTTPRequestParse parse(request);
	parse.parse(example);
	EXPECT_EQ(request.getMethod(), "GET");
	EXPECT_EQ(request.getUri(), "/cgi/index.html");
	EXPECT_EQ(request.getVersion(), "HTTP/1.1");
	EXPECT_EQ(request.getHeaders()["Host"], "localhost:4242");
	EXPECT_EQ(request.getHeaders()["Connection"], "keep-alive");
	EXPECT_EQ(request.getHeaders()["sec-ch-ua"], "\"Not_A Brand\";v=\"8\", \"Chromium\";v=\"120\", \"Google Chrome\";v=\"120\"");
}

TEST(HTTPRequestParseTest, locationTest) {
	HTTPRequest request;
	HTTPRequestParse parse(request);
	parse.parse(example);
	EXPECT_EQ(request.getLocation(), "/cgi/");
}