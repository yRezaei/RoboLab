/*
* renderableComponent.h
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
#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H

#include <memory>
#include "icomponent.h"
#include "../../graphics/mesh3D.h"
#include "../../mathematic/math3D.h"

namespace robolab {
	using namespace graphics;

	namespace entity {
		namespace component {

			class RenderableComponent : public IComponent
			{
			private:
				std::shared_ptr<GLBufferIDs> bufferIDs;
				std::shared_ptr<GLShaderIDs> shaderIDs;
				//std::shared_ptr<RenderableObject> renderableData;
			public:
				int index;
				bool isVisible;
			public:
				RenderableComponent(const std::string& meshName);
				~RenderableComponent();
			public:
				void init() override;
				const std::shared_ptr<GLBufferIDs> getGLBufferIDs();
				const std::shared_ptr<GLShaderIDs> getGLShaderIDs();
			};
		}
	}
}

#endif // !RENDERABLE_COMPONENT_H



