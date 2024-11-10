#!/usr/bin/env python

import os

def findChapterDirs(sourceDir):

    chapterDirs = {}

    for item in os.listdir(sourceDir):
        fullPath = os.path.join(sourceDir, item)
        if os.path.isdir(fullPath):
            if fullPath.find("ch_")!=-1:
                chapterDirs[item] = fullPath
            
    return chapterDirs
    
def findSourceFiles(chapterDirs):

    chapterSourceFiles = {}

    for chapter in chapterDirs:
        for item in os.listdir(chapterDirs[chapter]):
            fullFilename = os.path.join(chapterDirs[chapter], item)
            if os.path.isfile(fullFilename):
                if item.find(".cpp")!=-1:
                    if not item.find(".cpp~")!=-1:
                        if chapter in chapterSourceFiles:
                            chapterSourceFiles[chapter].append(item)
                        else:
                            chapterSourceFiles[chapter] = []
                            chapterSourceFiles[chapter].append(item)
                        
    return chapterSourceFiles
    
def createMarkdownChapters(sourceDir, chapterSourceFiles):

    latexFile = open("cpp_chapters.tex", "w")

    for chapter in chapterSourceFiles:
        latexFile.write("\\input{%s}\n" % chapter)
        print("Generating:", chapter+".md")
        markdownFile = open(chapter+".md", "w")
        markdownFile.write("# %s #\n" % chapter)
        markdownFile.write("\n")
        
        for sourceFile in chapterSourceFiles[chapter]:
            markdownFile.write("```cpp\n")
            markdownFile.write('<#include "%s">\n' % (os.path.join(os.path.join(sourceDir, chapter), sourceFile)))
            markdownFile.write("```\n\n")
        
        markdownFile.close()
        
        os.system("gpp -H %s.md | pandoc -f markdown -t latex -o %s.tex" % (chapter, chapter))
        
    latexFile.close()
    
if __name__ == "__main__":

    sourceDir = ".."
    absSourceDir = os.path.abspath(sourceDir)
    chapterDirs = findChapterDirs(sourceDir)
    chapterSourceFiles = findSourceFiles(chapterDirs)
    createMarkdownChapters(sourceDir, chapterSourceFiles)
    
    print(chapterSourceFiles)