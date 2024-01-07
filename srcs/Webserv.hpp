#pragma once

#include <iostream>
#include <string>

#include "Color.hpp"

# define CRLF "\r\n"
# define SP " "
# define SERVER_NAME	"webserv/1.0"
# define HTTP_VERSION	"HTTP/1.1"
# define DEFAULT_CONFIG_FILE "./config/default.conf"

# define DISALLOW_COPY_AND_ASSIGN(ClassName) \
	ClassName(const ClassName &); \
	ClassName &operator=(const ClassName &)
# define DISALLOW_ASSIGN(ClassName) \
	ClassName &operator=(const ClassName &)
# define DISALLOW_COPY(ClassName) \
	ClassName(const ClassName &)