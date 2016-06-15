#include "FileIO.h"

namespace robolab {
	namespace utils {

		namespace fileIO
		{
			namespace obj {

				using Poco::StringTokenizer;
				using Poco::NumberParser;

				LineDataType getLineType(const std::string& line) {
					if (line == "v")
						return OBJ_VERTEX;
					if (line == "vn")
						return OBJ_NORMAL;
					if (line == "vt")
						return OBJ_TEXTURE_COORDINATE;
					if (line == "f")
						return OBJ_FACE;
					if (line == "g")
						return OBJ_GROUP_NAME;
					if (line == "mtllib")
						return OBJ_MATERIAL_FILE;
					if (line == "usemtl")
						return OBJ_USE_MATERIAL;
					if (line == "newmtl")
						return OBJ_NEW_MATERIAL;
					if (line == "Ka")
						return OBJ_AMBIENT_COLOR;
					if (line == "Kd")
						return OBJ_DIFFUSE_COLOR;
					if (line == "Ks")
						return OBJ_SPECULAR_COLOR;
					if (line == "d")
						return OBJ_TRANSPARENT_VALUE;
					if (line == "illum")
						return OBJ_ILLUMINATION_VALUE;
					return OBJ_NONE;
				}

				void readMaterialProperties(const std::string& colroName, std::unordered_map<std::string, Vec3f>& colorMap, std::ifstream& file) {
					std::string line;
					while (file.good())
					{
						getline(file, line);
						StringTokenizer materialPropertyTokens(line, "\\, ", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
						if (materialPropertyTokens.count() == 0)
							continue;
						//colorMap[colroName] = Material();
						switch (getLineType(materialPropertyTokens[0]))
						{
						/*case OBJ_AMBIENT_COLOR:
							colorMap[colroName] = Vec3f(
								(float)NumberParser::parseFloat(materialPropertyTokens[1]),
								(float)NumberParser::parseFloat(materialPropertyTokens[2]),
								(float)NumberParser::parseFloat(materialPropertyTokens[3])
								);
							break;*/
						case OBJ_DIFFUSE_COLOR:
							colorMap[colroName] = Vec3f(
								(float)NumberParser::parseFloat(materialPropertyTokens[1]),
								(float)NumberParser::parseFloat(materialPropertyTokens[2]),
								(float)NumberParser::parseFloat(materialPropertyTokens[3])
								);
							
							break;
						/*case OBJ_SPECULAR_COLOR:
							colorMap[colroName].specularColor = Vec3f(
								(float)NumberParser::parseFloat(materialPropertyTokens[1]),
								(float)NumberParser::parseFloat(materialPropertyTokens[2]),
								(float)NumberParser::parseFloat(materialPropertyTokens[3])
								);
							break;
						case OBJ_TRANSPARENT_VALUE:
							colorMap[colroName].transparancy = (float)NumberParser::parseFloat(materialPropertyTokens[1]);
							break;
						case OBJ_ILLUMINATION_VALUE:
							break;*/
						case OBJ_NEW_MATERIAL:
							readMaterialProperties(materialPropertyTokens[1], colorMap, file);
							break;
						default:
							break;
						}
					}
				}

				void readMtlData(const std::string& mtlFileName, std::unordered_map<std::string, Vec3f>& colorMap) {
					std::ifstream mtlFile;
					std::string line;
					mtlFile.open((mtlFileName + ".mtl").c_str());

					if (mtlFile.is_open())
					{
						while (mtlFile.good())
						{
							getline(mtlFile, line);
							StringTokenizer mtlLineTokens(line, " ", StringTokenizer::TOK_TRIM);
							if (mtlLineTokens.count() == 0)
								continue;
							switch (getLineType(mtlLineTokens[0]))
							{
							case OBJ_NEW_MATERIAL:
							{
								readMaterialProperties(mtlLineTokens[1], colorMap, mtlFile);
							}
							break;

							default:
								break;
							}
						}
					}
					if (mtlFile.is_open())
						mtlFile.close();
				}

				std::shared_ptr<Mesh> load(const Path& filePath, Vec3f& preScale)
				{
					Mesh mesh;
					std::ifstream objFile;
					std::unordered_map<std::string, Vec3f> colorData;
					std::string line;
					Vec3f activeColor(0.5f, 0.5f, 0.5f);

					objFile.open(filePath.toString().c_str());
					if (objFile.is_open())
					{
						while (objFile.good())
						{
							getline(objFile, line);

							StringTokenizer objLineTokens(line, "/ ", StringTokenizer::TOK_TRIM);
							if (objLineTokens.count() == 0)
								continue;
							switch (getLineType(objLineTokens[0]))
							{
							case OBJ_VERTEX:
							{
								mesh.addVertex( Vec3f( (float)NumberParser::parseFloat(objLineTokens[1]) * preScale.x,
									(float)NumberParser::parseFloat(objLineTokens[2]) * preScale.y,
									(float)NumberParser::parseFloat(objLineTokens[3]) * preScale.z) );
							}
							break;

							case OBJ_FACE:
							{
								mesh.addTriangles(NumberParser::parseUnsigned(objLineTokens[1]) - 1, 
									NumberParser::parseUnsigned(objLineTokens[4]) - 1, 
									NumberParser::parseUnsigned(objLineTokens[7]) - 1, activeColor);
							}
							break;

							case OBJ_MATERIAL_FILE:
								readMtlData(filePath.toString().substr(0, filePath.toString().length() - 4), colorData);
								break;

							case OBJ_USE_MATERIAL:
								activeColor = colorData[objLineTokens[1]];
								break;
							}
						}
					}
					if (objFile.is_open())
						objFile.close();

					return std::make_shared<Mesh>(mesh);
				}
			}
		}
	}
}
