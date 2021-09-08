#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "token.hpp"


std::vector<token_t> lex(std::stringstream);
