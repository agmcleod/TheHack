//
//  ResolvePath.h
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-20.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#ifndef __TheHack__ResolvePath__
#define __TheHack__ResolvePath__

#include <stdio.h>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#elif _WIN32
inline std::string resourcePath() { return ""; }
#elif _WIN64
inline std::string resourcePath() { return ""; }
#endif

#endif /* defined(__TheHack__ResolvePath__) */
