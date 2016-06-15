/*
* fileIO.h
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
#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include "tinyxml2.h"

#include "../commen/dataTypes.h"
#include "../mathematic/math3D.h"
#include "../graphics/mesh3D.h"
#include "../graphics/mesh.h"

namespace robolab {
	using namespace math3D;
	using namespace graphics;

	namespace utils {

	
		/********************************************
		*		      namespace IO
		*********************************************/
		namespace fileIO
		{
			/********************************************
			*		      namespace obj
			*********************************************/
			namespace obj
			{
				using BitwiseDataFlag = int;

				enum FlagTypes {
					GENERATE_BOUNDING_BOX = 1,
					GENERATE_OPENGL_DATA = 2,
					RECALCULATE_NORMALS = 4
				};

				enum LineDataType {
					OBJ_VERTEX, OBJ_NORMAL, OBJ_TEXTURE_COORDINATE, OBJ_FACE, OBJ_GROUP_NAME,
					OBJ_MATERIAL_FILE, OBJ_USE_MATERIAL, OBJ_NEW_MATERIAL, OBJ_AMBIENT_COLOR,
					OBJ_DIFFUSE_COLOR, OBJ_SPECULAR_COLOR, OBJ_TRANSPARENT_VALUE, OBJ_ILLUMINATION_VALUE, OBJ_NONE
				};

				std::shared_ptr<Mesh> load(const Path& filePath, Vec3f& preScale = Vec3f(1.0f));

				LineDataType getLineType(const std::string& line);
				void readMaterialProperties(const std::string& colroName, std::unordered_map<std::string, Vec3f>& colorMap, std::ifstream& file);
				void readMtlData(const std::string& mtlFileName, std::unordered_map<std::string, Vec3f>& colorMap);
			}// end of namespace obj

		}// end of namespace FileIO

	}
}

#endif // FILEIO_H
