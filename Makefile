
all:
	g++ -std=c++17 app_1.cpp DiaryManager.cpp Entry.cpp Date.cpp MorseConverter.cpp -o app_1
	g++ -std=c++17 app_2.cpp DiaryReader.cpp Entry.cpp Date.cpp MorseConverter.cpp -o app_2
