#include "SceneLoader.h"

Scene SceneLoader::LoadNew(const char* filename) {

	std::fstream file;
	file.open(filename, std::ios::in);
	if (!file)
		int y = 9;//debug
	//initialize arrays to hold object definitions in the scene file
	std::vector<ModelTemplate> modelTemplates;
	int modelTemplate_i = 0;
	std::vector<WorldObjectTemplate> worldObjectTemplates;
	int worldObjectTemplate_i = 0;

	//buffer to hold strings temporarily while reading
	char* stringBuffer = new char[100];

	//marks the last read character
	char marker;

	//navigates to the first section -> Definitions
	do { marker = FileHandler::getNextRelevantChar(file); } while (marker != '>');
	marker = FileHandler::readHRString(file,stringBuffer);// "Definitions"

	while (marker != '>') {

		marker = FileHandler::readHRString(file, stringBuffer);

		//read model data
		if (strcmp(stringBuffer,"model")==0) {
			modelTemplates.push_back(ModelTemplate());
			marker = FileHandler::getNextRelevantChar(file); // '{'
			while (marker != '}') {
				marker = FileHandler::readHRString(file, stringBuffer);
				if (strcmp(stringBuffer, "name") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRString(file, stringBuffer);
					CopyStringData(&(modelTemplates[modelTemplate_i]).name, &stringBuffer);
				}
				else if (strcmp(stringBuffer, "filename") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRString(file, stringBuffer);
					CopyStringData(&(modelTemplates[modelTemplate_i]).filename, &stringBuffer);
				}//NOTE:: find a way to make sure that all fields are initialized?

				marker = FileHandler::getNextRelevantChar(file); // ',' or '}'
			}
			modelTemplate_i++;
		}
		marker = FileHandler::getNextRelevantChar(file); //'{' or '>'
	}

	marker = FileHandler::readHRString(file, stringBuffer);// "ObjectDeclarations"
	while (marker != '>') {

		marker = FileHandler::readHRString(file, stringBuffer);

		//read worldobject data
		if (strcmp(stringBuffer, "worldObject") == 0) {
			worldObjectTemplates.push_back(WorldObjectTemplate());
			marker = FileHandler::getNextRelevantChar(file); // '{'
			while (marker != '}') {
				marker = FileHandler::readHRString(file, stringBuffer);
				if (strcmp(stringBuffer, "name") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRString(file, stringBuffer);
					CopyStringData(&(worldObjectTemplates[worldObjectTemplate_i]).name, &stringBuffer);
				}
				else if (strcmp(stringBuffer, "model") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRString(file, stringBuffer);
					CopyStringData(&(worldObjectTemplates[worldObjectTemplate_i]).model, &stringBuffer);
				}
				else if (strcmp(stringBuffer, "position") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRVector3(file, (worldObjectTemplates[worldObjectTemplate_i]).position);
				}
				else if (strcmp(stringBuffer, "scale") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRVector3(file, (worldObjectTemplates[worldObjectTemplate_i]).scale);
				}
				else if (strcmp(stringBuffer, "eulerAngles") == 0) {
					marker = FileHandler::getNextRelevantChar(file); // ':'
					marker = FileHandler::readHRVector3(file, (worldObjectTemplates[worldObjectTemplate_i]).eulerAngles);
				}
				marker = FileHandler::getNextRelevantChar(file); // ',' or '}'
			}
			worldObjectTemplate_i++;
		}
		marker = FileHandler::getNextRelevantChar(file); //'{' or '>'
	}
	// "End"

	Scene newScene;
	newScene.mainCamera = PerspectiveCamera(45.0, (GLfloat)WINDOW_WIDTH / WINDOW_HEIGHT, 0.5f, 30.0f);

	newScene.mainCamera.position = glm::vec4(0, 0, -5, 1);
	newScene.mainCamera.eulerAngles = glm::vec3(0, 0, 0);

	newScene.lightSources = new PointLight();
	newScene.lightSourceCount = 1;

	newScene.ambientLight = glm::vec4(0.50, 0.0, 0.0, 1.0);

	newScene.worldObjectCount = worldObjectTemplate_i;
	newScene.worldObjects = new WorldObject[newScene.worldObjectCount];

	for (int i = 0;i < worldObjectTemplate_i;i++) {
		//char* pointers are stored in dynamic memory - so will persist after the function ends as well
		newScene.worldObjects[i] = GraphicsData::GetDefaultCube();
		newScene.worldObjects[i].name = worldObjectTemplates[i].name;
		newScene.worldObjects[i].position = glm::vec4(worldObjectTemplates[i].position, 1.0f);
		newScene.worldObjects[i].scale = glm::vec4(worldObjectTemplates[i].scale, 1.0f);
		newScene.worldObjects[i].eulerAngles = glm::vec4(worldObjectTemplates[i].eulerAngles*DEG_TO_RAD, 1.0f);
	}

	return newScene;
}
