//
// NewClassMaker
//
// Copyright 2001, 2007, 2009 Sony Corporation
//

●スクリプト本体
	newClassMaker
	(このディレクトリでmakeすると作られます)

●目的
	クラスなんか大量に作るものなのに、ヘッダ情報を書いたり
	面倒なことが多い。このスクリプトを使えばなんの手間もなく
	doxygenに対応したクラスが作られる。

●注意
	※本スクリプトを使うともともとのファイルを上書きしてしまいますので
	悲しい事故が起きないように充分注意して使ってください。

●使用方法
	まず、このスクリプトをmakeしておきます。
	> cmake   SAP_Toy_Alive_Asobi_Prototypes/tools/NewClassMaker --build SAP_Toy_Alive_Asobi_Prototypes/tools/NewClassMaker
	> make -C SAP_Toy_Alive_Asobi_Prototypes/tools/NewClassMaker

	その上で、新規クラスを作るときは
	> SAP_Toy_Alive_Asobi_Prototypes/tools/NewClassMaker/newClassMaker MyClass

●自動生成されるもの

	MyClass.h    ヘッダ
	MyClass.cpp  ソース
