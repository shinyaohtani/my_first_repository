// **************************************************************************************
// ファイル名    NewClassMaker.cp
// Copyright 2001-2008,2009 <大谷伸弥>. All rights reserved.
// 内容
// **************************************************************************************
// 修正履歴
// 2001年 5月 18日 金曜日 - オリジナル
// 2007年 6月  1日 金曜日 - Initを消した
// 2009年11月  5日 金曜日 - 第3引数と第4引数で、作成情報のみテンプレートうことを可能に
// 2015年 4月 10日 金曜日 - valid_を利用するように変更。
// **************************************************************************************

#include <cstdio>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

int main(const int argv, const char** argc)
{
	bool indicated=false;
	string classname;
	if (argv == 1) {
		printf("Insert the new class name.  New class name: ");
		getline(cin, classname);
	} else {
		classname.assign(argc[1]);
		indicated=true;
	}

	string classdeclaration;
	string classdefinition;
	if (argv >= 3) {
		ifstream fin(argc[2]);
		if (fin.is_open() && fin.good() && !fin.eof()) {
			string tmpstr;
			for (uint32_t line=0; getline(fin, tmpstr, '\n'); ++line) {
				classdeclaration.append(tmpstr);
				classdeclaration.append("\n");
			}
		} else {
			printf("Can't open file: %s",argc[2]);
			return 1;
		}
	}
	if (argv >= 4) {
		ifstream fin(argc[3]);
		if (fin.is_open() && fin.good() && !fin.eof()) {
			string tmpstr;
			for (uint32_t line=0; getline(fin, tmpstr, '\n'); ++line) {
				classdefinition.append(tmpstr);
				classdefinition.append("\n");
			}
		} else {
			printf("Can't open file: %s",argc[2]);
			return 1;
		}
	}
	char HeaderFileName[256];
	char SourceFileName[256];
	sprintf(HeaderFileName,"%s.h",classname.c_str());
	sprintf(SourceFileName,"%s.cpp",classname.c_str());


	FILE* HeaderFile = fopen(HeaderFileName, "w");
	FILE* SourceFile = fopen(SourceFileName, "w");
	if(HeaderFile==0 || SourceFile==0){
		printf("Error: Now in unable condition to make files. (Maybe there is same name files in the same folder.\n");
		if(HeaderFile != 0) fclose(HeaderFile);
		if(SourceFile != 0) fclose(SourceFile);
	}
	else{
		char ClassFeature[256];
		if(indicated==false){
			printf("\nInsert brief comment for the class \"%s\".\n\t:",classname.c_str());
			fgets(ClassFeature,256,stdin);
		} else {
			ClassFeature[0] = '\0';
		}

		time_t systime = time(NULL);
		struct tm* ltc = localtime(&systime);

		string dateStr(asctime(ltc));
		char yearStr[256];

		if(dateStr.size()){
			dateStr.erase(dateStr.size()-1);
		}
		strftime(yearStr,256,"%Y",ltc);

		system("\\rm -f .tmp_whoami.txt");
		system("whoami > .tmp_whoami.txt");
		ifstream ifs(".tmp_whoami.txt");
		istreambuf_iterator<char> it(ifs), last;
		string authorname(it, last);

		if (authorname[authorname.size()-1]=='\n') {
			authorname.erase(authorname.size()-1);
		}
		ifs.close();
		system("\\rm -f .tmp_whoami.txt");

		fprintf(HeaderFile,"//\n");
		fprintf(HeaderFile,"// %s.h\n",classname.c_str());
		fprintf(HeaderFile,"//\n");
		fprintf(HeaderFile,"// Copyright %s Sony Corporation\n",yearStr);
		fprintf(HeaderFile,"//\n");
		fprintf(HeaderFile,"\n");
		fprintf(HeaderFile,"//\n");
		fprintf(HeaderFile,"//!\\file\n");
		fprintf(HeaderFile,"//! \\brief Declaration of %s\n",classname.c_str());
		fprintf(HeaderFile,"//! \\author %s\n",authorname.c_str());
		fprintf(HeaderFile,"//! \\version\n");
		fprintf(HeaderFile,"//!     %s - Original\n",dateStr.c_str());
		fprintf(HeaderFile,"//\n");
		fprintf(HeaderFile,"\n");
		fprintf(HeaderFile,"#ifndef %s_H\n",classname.c_str());
		fprintf(HeaderFile,"#define %s_H\n",classname.c_str());
		fprintf(HeaderFile,"\n");
		fprintf(HeaderFile,"\n");
		if (classdeclaration.size() == 0) {
			fprintf(HeaderFile,"// Standard C++ headers\n");
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"// Installed library headers\n");
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"// Developing headers\n");
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"// ****************************************************************************\n");
			fprintf(HeaderFile,"//! @brief %s\n",ClassFeature);
			fprintf(HeaderFile,"//!\n");
			fprintf(HeaderFile,"//! %s\n",ClassFeature);
			fprintf(HeaderFile,"// ****************************************************************************\n");
			fprintf(HeaderFile,"class %s\n",classname.c_str());
			fprintf(HeaderFile,"{\n");
			fprintf(HeaderFile,"	public:\n");
			fprintf(HeaderFile,"		%s(void);\n",classname.c_str());
			fprintf(HeaderFile,"		virtual ~%s(void);\n",classname.c_str());
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"		bool    init();\n");
			fprintf(HeaderFile,"		bool    run();\n");
			fprintf(HeaderFile,"		bool    SampleFunc%s(const long inSampleArgument);\n",classname.c_str());
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"	private:\n");
			fprintf(HeaderFile,"		bool    handleKeyEvent(const int inKey);\n");
			fprintf(HeaderFile,"		//!     @brief The class validity.\n");
			fprintf(HeaderFile,"		//!\n");
			fprintf(HeaderFile,"		//!     If the initialization successfully finished, or not.\n");
			fprintf(HeaderFile,"		bool    valid_;\n");
			fprintf(HeaderFile,"\n");
			fprintf(HeaderFile,"};\n");
		} else {
			fprintf(HeaderFile,"%s",classdeclaration.c_str());
		}
		fprintf(HeaderFile,"\n");
		fprintf(HeaderFile,"#endif //%s_H\n",classname.c_str());

		fprintf(SourceFile,"//\n");
		fprintf(SourceFile,"// %s.cpp\n",classname.c_str());
		fprintf(SourceFile,"//\n");
		fprintf(SourceFile,"// Copyright %s Sony Corporation\n",yearStr);
		fprintf(SourceFile,"//\n");
		fprintf(SourceFile,"\n");
		fprintf(SourceFile,"//\n");
		fprintf(SourceFile,"//!\\file\n");
		fprintf(SourceFile,"//! \\brief Declaration of %s\n",classname.c_str());
		fprintf(SourceFile,"//! \\author %s\n",authorname.c_str());
		fprintf(SourceFile,"//! \\version\n");
		fprintf(SourceFile,"//!     %s - Original\n",dateStr.c_str());
		fprintf(SourceFile,"//\n");
		fprintf(SourceFile,"\n");
		fprintf(SourceFile,"#include \"%s.h\"\n",classname.c_str());
		fprintf(SourceFile,"\n");
		fprintf(SourceFile,"\n");
		if (classdefinition.size() == 0) {
			fprintf(SourceFile,"// Standard C++ headers\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// Installed library headers\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// Developing headers\n");
			fprintf(SourceFile,"#include <DebugUtil/kbhit.h> //!< Remove this. This is only for key_loop example in run()\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief The constructor of the \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This initializes the member valiables.\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"%s::%s(void) : valid_(true)\n",classname.c_str(),classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"}\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief The destructor of the \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This releases the member valiables.\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"%s::~%s(void)\n",classname.c_str(),classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"}\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief initializer of \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This does nothing. Only a sample of function definition.\n");
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! @return  If it successed or not..\n");
			fprintf(SourceFile,"//!     @retval true:       succeeded\n");
			fprintf(SourceFile,"//!     @retval false:      failed\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"bool \n");
			fprintf(SourceFile,"%s::init()\n",classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"	bool   noErr = true;\n");
			fprintf(SourceFile,"	return noErr;\n");
			fprintf(SourceFile,"}\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief runner of \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This does nothing. Only a sample of function definition.\n");
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! @return  If it successed or not..\n");
			fprintf(SourceFile,"//!     @retval true:       succeeded\n");
			fprintf(SourceFile,"//!     @retval false:      failed\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"bool \n");
			fprintf(SourceFile,"%s::run()\n",classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"	bool   noErr = true;\n");
			fprintf(SourceFile,"	for (bool loop=true; loop; ) { //!< Remove this event loop.\n");
			fprintf(SourceFile,"		int key = DebugUtil::KeyUtil::getKeyEvent(); //!< This is an example.\n");
			fprintf(SourceFile,"		//! Write main algorithms here\n\n\n");
			fprintf(SourceFile,"		//! and finally handle user command.\n");
			fprintf(SourceFile,"		key = (int)'q'; //!< Remove this. This cause immedate exit.\n");
			fprintf(SourceFile,"		loop = loop && handleKeyEvent(key);\n");
			fprintf(SourceFile,"	}\n");
			fprintf(SourceFile,"	return noErr;\n");
			fprintf(SourceFile,"}\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief Sample of \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This does nothing. Only a sample of function definition.\n");
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! @param  inSampleArgument [in]  Sample of argument.\n");
			fprintf(SourceFile,"//!     @arg 0-9: small object\n");
			fprintf(SourceFile,"//!     @arg 10-100: normal parameter\n");
			fprintf(SourceFile,"//! @return  If it successed or not..\n");
			fprintf(SourceFile,"//!     @retval true:       succeeded\n");
			fprintf(SourceFile,"//!     @retval false:      failed\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"bool \n");
			fprintf(SourceFile,"%s::SampleFunc%s(const long inSampleArgument)\n",classname.c_str(),classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"	bool   noErr = true;\n");
			fprintf(SourceFile,"	if (inSampleArgument > 100) {\n");
			fprintf(SourceFile,"		valid_ = false;\n");
			fprintf(SourceFile,"		noErr  = false;\n");
			fprintf(SourceFile,"	}\n");
			fprintf(SourceFile,"	return noErr;\n");
			fprintf(SourceFile,"}\n");
			fprintf(SourceFile,"\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"//! @brief Key handling sample \"%s\"\n",classname.c_str());
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! This does nothing. Only a sample of function definition.\n");
			fprintf(SourceFile,"//!\n");
			fprintf(SourceFile,"//! @param  inKey [in]  key code (getchar() etc...).\n");
			fprintf(SourceFile,"//! @return  If continue main loop or not..\n");
			fprintf(SourceFile,"//!     @retval true:       continue loop\n");
			fprintf(SourceFile,"//!     @retval false:      exit loop\n");
			fprintf(SourceFile,"// ****************************************************************************\n");
			fprintf(SourceFile,"bool \n");
			fprintf(SourceFile,"%s::handleKeyEvent(const int inKey)\n",classname.c_str());
			fprintf(SourceFile,"{\n");
			fprintf(SourceFile,"	bool loop=true;\n");
			fprintf(SourceFile,"	switch (inKey) {\n");
			fprintf(SourceFile,"		case 'q':\n");
			fprintf(SourceFile,"			loop = false;\n");
			fprintf(SourceFile,"			break;\n");
			fprintf(SourceFile,"		default:\n");
			fprintf(SourceFile,"			break;\n");
			fprintf(SourceFile,"	}\n");
			fprintf(SourceFile,"	return loop;\n");
			fprintf(SourceFile,"}\n");
		} else {
			fprintf(SourceFile,"%s",classdefinition.c_str());
		}

		fclose(HeaderFile);
		fclose(SourceFile);
		//printf("Successed to make new files named %s and %s.\n",SourceFileName,HeaderFileName);
	}

	return 0;
}
