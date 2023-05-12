cmake_minimum_required(VERSION 3.25)
project(ProjetD)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(ProjetD
        .idea/shelf/Uncommitted_changes_before_Update_at_11_05_2023_13_59_[Changes]/programme
        .idea/shelf/Uncommitted_changes_before_Update_at_11_05_2023_13_59_[Changes]/shelved.patch
        .idea/shelf/Uncommitted_changes_before_Update_at_11_05_2023_13_59__Changes_.xml
        .idea/.gitignore
        .idea/modules.xml
        .idea/ProjetD.iml
        .idea/vcs.xml
        .idea/workspace.xml
        .gitignore
        command.txt
        erreur.txt
        grand_nombre.c
        grand_nombre.h
        initialisation.c
        initialisation.h
        main.c
        programme)
