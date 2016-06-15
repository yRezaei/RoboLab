/*
 * dataTypes.h
 * 
 * Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include <Poco/StringTokenizer.h>
#include <Poco/RegularExpression.h>
#include <Poco/NumberParser.h>
#include <Poco/Format.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Random.h>

namespace robolab {
	using Path = Poco::Path;
}

#endif
