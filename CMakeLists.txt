###########################################################
###
### Detection systems by LIDAR Point Clouds
###
### (c) 2018 Shirao Shotaro - Enokida Labo
### CMakeLists.txt
###
### CMakeを使用してプロジェクトを生成することができます。
### Windowsの場合はCMakeGUIの使用をお勧めします。
###
### CMakeのバージョンは3.0.0以上を使用してください。
###
###########################################################

cmake_minimum_required(VERSION 3.0.0)

### プロジェクト名
# EXECUTABLE_NAMEの変数名を、プロジェクト名として変更します
set(EXECUTABLE_NAME "DS4gyro")
project(${EXECUTABLE_NAME})

### プロパティ設定
# ここはよくわかりません。。。
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

### プロジェクトのインクルードディレクトリ
# 「自分たちが用意するソースコードに対する」インクルードディレクトリです。
# PCLなどのライブラリは後程読み込みます。
set(PROJECT_INCLUDE_DIRECTORIES src/)

### ソースファイルの抽出
# ソースファイルを抽出し、プロジェクトへ読み込みます。
file(GLOB_RECURSE cpp_files src/*.c*)
file(GLOB_RECURSE header_files src/*.h*)

### プラットフォームに応じてオプションを変更
if(UNIX) # Linux

	# C++14を有効化し、マルチスレッド処理を実行します。
	# [TODO]最適化オプションは適切に選択すること
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g -O0 -L${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu")
	
	# X11によるマルチスレッド処理のライブラリを追加
	target_link_libraries(${PROJECT_NAME} X11 pthread)

elseif(WIN32) # Windows
	
	# ソースコードをutf8として扱うフラグ
	# CP932は滅べばいい。Windowsで新規ファイル作成すると、CP932（Shift-jis）で生成されるため、速攻でBOM UTF-8に変更せよ（戒め
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /execution-charset:utf-8")

endif(UNIX)

### プロジェクトの設定

# 実行可能ファイルの追加
add_executable(${EXECUTABLE_NAME} ${cpp_files} ${header_files})

# インクルードディレクトリの登録
include_directories(${PROJECT_INCLUDE_DIRECTORIES})

# ターゲットリンクの登録
target_link_libraries(${EXECUTABLE_NAME})

### Visual Studio用の、ソースグループ設定
#Visual Studioのフィルタを、ソースフォルダと全く同じ構造に組み立ててくれるもの
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

set(_source_list ${cpp_files} ${header_files})
assign_source_group(${_source_list})
### Visual Studio用のソースグループ設定、ここまで
