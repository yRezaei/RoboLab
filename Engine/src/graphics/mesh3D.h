/*
* mesh3D.h
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
#ifndef MESH_3D_H
#define MESH_3D_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>


namespace robolab {

	namespace graphics {

		struct GLBufferIDs {
		private:
			std::size_t uniqueID;
			std::string meshName;
		public:
			unsigned int VAO;
			std::unordered_map<std::string, unsigned int> attributesID;
			unsigned int indexID;
			std::size_t indexSize;
			GLBufferIDs(std::size_t UniqueID, unsigned int vao, unsigned int index, std::size_t IndexSize, std::unordered_map<std::string, unsigned int>& AttributesID)
				: uniqueID(UniqueID), VAO(vao), indexID(index), indexSize(IndexSize), attributesID(AttributesID) {}
			bool operator == (const GLBufferIDs& glBufferIDs)
			{
				if (uniqueID == glBufferIDs.uniqueID)
					return true;
				else
					return false;
			}

			const std::size_t& getID() {
				return uniqueID;
			}

		};

		struct GLShaderIDs {
			unsigned int shaderID;
			std::unordered_map<std::string, unsigned int> locationIDs;
			GLShaderIDs(unsigned int ShaderID, std::unordered_map<std::string, unsigned int>& LocationIDs)
				: shaderID(ShaderID), locationIDs(LocationIDs) {}
		};

		struct RenderableObject {
			std::size_t index;
			std::shared_ptr<GLBufferIDs> gLIDs;
			RenderableObject(std::size_t Index, std::shared_ptr<GLBufferIDs> GLIDs)
				: index(Index), gLIDs(GLIDs) {}
		};

		struct PhysicalProperty
		{
			float mass;
			float density;
			float friction;
			float dynamicFriction;
			float restitution;
			float angularDamping;
			float linearDamping;

			PhysicalProperty() {
				this->mass = 1.3f;
				this->density = 0.7f;
				this->friction = 0.7f;
				this->dynamicFriction = 0.7f;
				this->restitution = 0.4f;
				this->angularDamping = 0.3f;
				this->linearDamping = 0.3f;
			}

			PhysicalProperty(float mass, float density, float friction, float dynamicFriction,
				float restitution, float angularDamping, float linearDamping) {
				this->mass = mass;
				this->density = density;
				this->friction = friction;
				this->dynamicFriction = dynamicFriction;
				this->restitution = restitution;
				this->angularDamping = angularDamping;
				this->linearDamping = linearDamping;
			}
		};
	}
}


#endif // !MESH_DATA_H

