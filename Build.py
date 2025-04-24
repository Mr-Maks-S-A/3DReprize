#!/usr/bin/env python
# encoding: utf-8

# from art import tprint
    # tprint("Build CProject",font="puffy.flf",chr_ignore= True)
# import tqdm
# import time
    # for _ in tqdm.tqdm(range(100)):
    #     time.sleep(0.25)


import os
import errno 
import argparse
import shutil
import subprocess

from enum import Enum

#==============================Base

class Directory(Enum):
    def __str__(self):
        return str(self.value)
    
    CurrentPyFile:str   = os.path.realpath(__file__)
    Project:str         = os.path.dirname(CurrentPyFile)+"\\"
    Oll_Output:str      = "Out"
    Src:str             = "Src"
    Build:str           = "Build"

class Platform(Enum):
    def __str__(self):
        return str(self.value)
    
    X64:str = "x64"
    X86:str = "x86"

class OC(Enum):
    def __str__(self):
        return str(self.value)
    
    Windows:str     = "Windows"
    Linux:str       = "Linux"
    Mac:str         = ""      #non

class BuildType(Enum):
    def __str__(self):
        return str(self.value)
    
    Debug:str       = "Debug"
    Release:str     = "Release"
    
    
    
#ref: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
class Generators(Enum):
    def __str__(self):
        return str(self.value)
    
    MSVS:str    ="Visual Studio 17 2022"       #non
            # Visual Studio 6
            # Visual Studio 7
            # Visual Studio 7 .NET 2003
            # Visual Studio 8 2005
            # Visual Studio 9 2008
            # Visual Studio 10 2010
            # Visual Studio 11 2012
            # Visual Studio 12 2013
            # Visual Studio 14 2015
            # Visual Studio 15 2017
            # Visual Studio 16 2019

    Ninja:str ="Ninja"
            # Ninja Multi-Config

    Make:str ="MinGW Makefiles"    
            # Borland Makefiles
            # MSYS Makefiles
            # NMake Makefiles
            # NMake Makefiles JOM
            # Unix Makefiles
            # Watcom WMake

    Other_Generators:str =""            #non
            # Green Hills MULTI
            # Xcode
   
    Extra_Generators:str =""            #non
            # CodeBlocks
            # CodeLite
            # Eclipse CDT4
            # Kate
            # Sublime Text 2
            
class Compiler(Enum):
    def __str__(self):
       return str(self.value)
    
    Mingw:str = "gcc"
            # c++
            # g++
            
    Clang:str = "clang"
            
class Cmake_Flags(Enum):
    def __str__(self):
        return str(self.value)
    
    FRESH_ARG:str = "--fresh" 
    CLEAN_ARG:str = "--clean-first" 
    VERBOSE_ARG:str = "--verbose" 

class Cmake_Commands(Enum):
    def __str__(self):
        return str(self.value)
    Configure:str
    Build:str

class Action(Enum):
    def __str__(self):
        return str(self.value)
    CLEANING:str = "clean"
    GENERATE:str = "generate"
    BUILD:str = "build"
    CLANG_FORMAT:str = "clang_format"
    
    
#==============================Config
configs ={"base":{
                "OUT_DIR":str(Directory.Oll_Output),
                "SOURCE_DIR":str(Directory.Src),
                "BUILD_FOLDER":str(Directory.Build),
                "GENERATOR":str(Generators.Make),
                "COMPILER":str(Compiler.Mingw),
                "PLATFORM":str(Platform.X64),
                "OC":str(OC.Windows),
                "BuildType":str(BuildType.Debug),
                "FRESH": True,
                "CLEAN ": True,
                "VERBOSE ": False,
            }
        }



#==============================metods
def Create_or_Delete_dirs(path_to_dir:str,delete_if_exeist:bool = False)->bool:
    if (not os.path.exists(path_to_dir) and not delete_if_exeist):
        os.makedirs(path_to_dir)
        return True 
    elif(os.path.exists(path_to_dir)):
        os.removedirs(path_to_dir)
        return True 
    else:
        return False 




def passage(file_name, folder):
    for element in os.scandir(folder):
        if element.is_file():
            if element.name == file_name:
                yield folder
        else:
            yield from passage(file_name, element.path)




if __name__ == "__main__":
    
    # print ('\n'.join(os.environ['PATH'].split(';')))
    # Create_or_Delete_dir(base_config["OUT_DIR"])
    
    
    # print(*passage("gcc.exe", "C:\\w64devkit"))  # C:\Scripts\new1\libs
    # print(passage("clang.exe", "C:\\"))  # C:\Scripts\new1\libs
    

#для обновление Submodule
# git submodule init 
# git submodule update