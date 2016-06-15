/*
* resource.h
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
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include "../commen/dataTypes.h"
#include "../graphics/mesh.h"

namespace robolab {
	using namespace graphics;

	namespace manager {

		namespace internal
		{
			inline std::size_t getUniqueMeshID() noexcept
			{
				static std::size_t lastMeshID{ 0u };
				return lastMeshID++;
			}
		}

		class Resource {
		public:
			enum class MeshUsageType {
				VISUALIZATION,
				PHYSIC_SIMULATION
			};
			
		private:
			enum FileExtention {
				FILE_OBJ,
				FILE_STL
			};
			static bool isInitialized;
		private:
			static std::vector<std::shared_ptr<Mesh>> emptyPhysicalMesh;
			static std::unordered_map<std::string, FileExtention> filesExtentionList;
			static std::unordered_map<std::string, std::shared_ptr<Mesh>> visualMeshList;
			static std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> physicalMeshList;
			
			static std::shared_ptr<Mesh> loadMesh(const Path& path, Vec3f& scaleFactor);
		public:
			static bool initialize();
			
			static void loadMesh(MeshUsageType type, const std::string& directory, const std::string& baseName, Vec3f& scaleFactor = Vec3f(1.0f));
			static const std::pair<bool, std::shared_ptr<Mesh>> getVisualMesh(const std::string& meshName);
			static const std::pair<bool, std::vector<std::shared_ptr<Mesh>>> getPhysicalMesh(const std::string& meshName);
			static std::shared_ptr<Mesh> createCube(const std::string& meshName, float lenght, float width, float height, Vec3f& pivot);
			static void shutdown();
		};

	}
}
#endif // !RESOURCE_H

