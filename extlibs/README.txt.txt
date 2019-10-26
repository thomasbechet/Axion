-GLEW:
	-Included in OpenGL renderer system.
-GLFW:
	-Included in GLFW window system.
-RapidXml:
	-Not included.
-STB:
	-Included in Core system for image loading.
-TinyObjLoader:
	-Included in Core system for obj mesh object loading.
-Others:
	-nlohmann_json:
		-Included in the Core system for json parsing. 
		 The json.hpp header is direcltly in the source 
		 code to ensure access by others modules without
		 including the header file.
		 The file is currently located in Core/Utility/Json.hpp
