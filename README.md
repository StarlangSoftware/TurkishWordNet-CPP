Turkish WordNet KeNet
============

# WordNet

Wordnet, in its broader definition, is a highly comprehensive dictionary that is built on distinct word senses along with their definitions. Most of the words in a wordnet are open-class words such as nouns, verbs, adjectives and adverbs. Main building blocks of a wordnet are synsets, which are comprised of synonym synset members. Synsets are the distinct units in wordnets and all the mappings including intra and interlingual ones are constructed based on the synsets. In lexical semantics, it is argued that words can be defined based on the relations between them. Adopting this principle, wordnets map semantic relations such as hypernymy, meronymy or antonymy through synsets.

Constructing a wordnet, whether from scratch or by expanding a previous one, is a labor intensive process that requires several steps and extensive use of both human labor and automated systems. Since the creation of the first wordnet Princeton WordNet (PWN) in 1995 (Miller, 1995), many other wordnets have been created for several languages (e.g., Finnish WordNet FinnWordNet (Linden and Carlson, 2010), Polish WordNet (Derwojedowa et al., 2008), Norwegian WordNet (Fjeld and Nygaard, 2009), Danish WordNet (Pedersen et al., 2009), French WordNet WOLF (Sagot, 2008)). In addition, multilingual wordnets linking the wordnets of multiple languages have been created. To exemplify, EuroWordNet (EWN) is a multilingual WordNet project that consists several European languages (English, Dutch, Italian, Spanish, German, French, Czech and Estonian) (Vossen, 2007). In EWN, the wordnets were created for each language separately and then linked through an Inter-Lingual-Index based on PWN. BalkaNet, similar to EWN, is a multilingual wordnet project consisting of six Balkan languages (Bulgarian, Czech, Greek, Romanian, Serbian, and Turkish) (Tufis et al., 2004). This project was done to produce a multilingual semantic network, fully compatible with EWN and its extensions.

# Turkish WordNet

The very first step in constructing KeNet, as in every other wordnet, was to create synsets. Synset can be defined as a group of words sharing the same sense and part of speech (POS). Regarding the construction of these synsets, the first version of the database was constructed through mining of the latest Contemporary Dic- tionary of Turkish (CDT) (2011’s print) published by the Turkish Language Institute (TLI) (Ehsani et al., 2018). By convention, CDT marks synonyms by using commas such that synonyms of a word are given after its definition with a separation of comma. To decide on true synonyms that must occur in the same synsets, we sliced the definitions at commas and listed the comma-separated lemmas and the rest of the definitions as candidates of synonyms. Then, those lists were displayed for linguistically-informed human annotators who decided on the synonymy relation between the lem- mas and the definitions. 49,774 pairs were annotated at the end of this phase. Although some of them were included as separate entries in CDT, passivized and causativized forms of verbs were deleted from KeNet as they share the same root with their active forms.

Although the vast majority of the synsets were constructed during this process, there was a need for follow-up procedures to improve the organization of the current synsets. Since the main problem encountered in synset construction was the semantic relatedness of the synset members, two other procedures were followed in order to control the synonymy relations within the synsets: the merge process and the split process.

## Merge Process

In the merge process, different synsets that should be grouped together were identified and grouped as a single synset. Three things were crucial while merging the synsets: (i) having a single and unique definition for each synset, (ii) having true synonyms as synset members in each synset and (iii) having a representative first synset member in each synset. Firstly, the synsets that were created by combining the synset members with identical senses had as many definitions as the number of synset members in them since the definitions were also merged while merging the synset members. The definitions of the merged synsets were initially combined with a pipe symbol in between them. A new definition for each merged synset was written so that each synset had a single and unique definition that covers the meaning of all its synset members. None of the synset members of a synset appeared in its definition. In this process, new definitions for 10,612 number of synsets were written by the human annotators. Secondly, some synsets were found to include unrelated synset members. Therefore, another goal of the merge process was to include only the synset members that were synonyms. 1,144 number of synsets with unrelated synset members that had been identified in other parts of the work were transferred to the split process.

## Split Process

In the split process, the synsets that included synset members with different senses were split and separate synsets were created for each group of related synset members. In order to fix this problem, we created a pool where we collected all the synsets that had unrelated synset members. We displayed these synsets on Google Sheets. Linguistically-informed human annotators then split these wrongly-merged synsets and wrote new definitions for the newly-created ones.

Currently, there are 77,330 synsets, 109,049 synset members and 80,956 distinct synset members in KeNet. The POS categories that are included are nouns, adverbs, adjectives, adverbs, interjections, pronouns, postpositions and conjunctions.

|Part of Speech|# of Synsets|
|---|---|
|Nouns|44,074|
|Verbs|17,791|
|Adjectives|12,416|
|Adverbs|2,550|
|Interjections|342|
|Pronouns|68|
|Conjunctions|60|
|Postpositions|29|
|Total|77,330|

## Data Format

The structure of a sample synset is as follows:

	<SYNSET>
		<ID>TUR10-0038510</ID>
		<LITERAL>anne<SENSE>2</SENSE>
		</LITERAL>
		<POS>n</POS>
		<DEF>...</DEF>
		<EXAMPLE>...</EXAMPLE>
	</SYNSET>

Each entry in the dictionary is enclosed by \<SYNSET> and \</SYNSET> tags. Synset members are represented as literals and their sense numbers. \<ID> shows the unique identifier given to the synset. \<POS> and \<DEF> tags denote part of speech and definition, respectively. As for the \<EXAMPLE> tag, it gives a sample sentence for the synset.
	
Video Lectures
============

[<img src="https://github.com/StarlangSoftware/TurkishWordNet/blob/master/video1.jpg" width="50%">](https://youtu.be/RLVTegHva_k)[<img src="https://github.com/StarlangSoftware/TurkishWordNet/blob/master/video2.jpg" width="50%">](https://youtu.be/DFc_XEqJshU)[<img src="https://github.com/StarlangSoftware/TurkishWordNet/blob/master/video3.jpg" width="50%">](https://youtu.be/KyA32rOv308)

For Developers
============

You can also see [Java](https://github.com/starlangsoftware/TurkishWordNet), [Python](https://github.com/starlangsoftware/TurkishWordNet-Py), [C](https://github.com/starlangsoftware/TurkishWordNet-C), [Cython](https://github.com/starlangsoftware/TurkishWordNet-Cy), [Swift](https://github.com/starlangsoftware/TurkishWordNet-Swift), [Js](https://github.com/starlangsoftware/TurkishWordNet-Js), or [C#](https://github.com/starlangsoftware/TurkishWordNet-CS) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called TurkishWordNet-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/TurkishWordNet-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run TestWordNet.cpp .

Detailed Description
============

+ [WordNet](#wordnet)
+ [SynSet](#synset)
+ [Synonym](#synonym)

## WordNet

To load the WordNet KeNet,

	WordNet* a = new WordNet();

To load a particular WordNet,

	WordNet* domain = new WordNet("domain_wordnet.xml");

To bring all the synsets,

	vector<SynSet> synSetList()

To bring a particular synset,

	SynSet getSynSetWithId(string synSetId)

And, to bring all the meanings (Synsets) of a particular word, the following is used.

	vector<SynSet> getSynSetsWithLiteral(string literal)

## SynSet

Synonym is procured in order to find the synonymous literals of a synset.

	Synonym getSynonym()
	
In order to obtain the Relations inside a synset as index based, the following method is used.

	Relation getRelation(int index)

For instance, all the relations in a synset,

	for (int i = 0; i < synset.relationSize(); i++){
		relation = synset.getRelation(i);
		...
	}

## Synonym

The literals inside the Synonym can be found as index based with the following method.

	Literal getLiteral(int index)

For example, all the literals inside a synonym can be found with the following:

	for (int i = 0; i < synonym.literalSize(); i++){
		literal = synonym.getLiteral(i);
		...
	}

# Cite

	@inproceedings{bakay21,
 	title={{T}urkish {W}ord{N}et {K}e{N}et},
 	year={2021},
 	author={O. Bakay and O. Ergelen and E. Sarmis and S. Yildirim and A. Kocabalcioglu and B. N. Arican and M. Ozcelik and E. Saniyar and O. Kuyrukcu and B. 	Avar and O. T. Y{\i}ld{\i}z},
 	booktitle={Proceedings of GWC 2021}
 	}

For Contibutors
============

### Conan Setup

1. First install conan.

pip install conan

Instructions are given in the following page:

https://docs.conan.io/2/installation.html

2. Add conan remote 'ozyegin' with IP: 104.247.163.162 with the following command:

conan remote add ozyegin http://104.247.163.162:8081/artifactory/api/conan/conan-local --insert

3. Use the comman conan list to check for installed packages. Probably there are no installed packages.

conan list

### conanfile.py file

1. Put the correct dependencies in the requires part
```
    requires = ["math/1.0.0", "classification/1.0.0"]
```

2. Default settings are:
```
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}
    exports_sources = "src/*", "Test/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(conanfile=self, keep_path=False, src=join(self.source_folder), dst=join(self.package_folder, "include"), pattern="*.h")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.a")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.so")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.dylib")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "bin"), pattern="*.dll")

    def package_info(self):
        self.cpp_info.libs = ["ComputationalGraph"]
```

### CMakeLists.txt file
1. Set the C++ standard with compiler flags.
```
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_FLAGS "-O3")
```
2. Dependent packages should be given with find_package.
```
	find_package(util_c REQUIRED)
	find_package(data_structure_c REQUIRED)
```
3. For library part, use add_library and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_library(Math src/Distribution.cpp src/Distribution.h src/DiscreteDistribution.cpp src/DiscreteDistribution.h src/Vector.cpp src/Vector.h src/Eigenvector.cpp src/Eigenvector.h src/Matrix.cpp src/Matrix.h src/Tensor.cpp src/Tensor.h)
	target_link_libraries(Math util_c::util_c data_structure_c::data_structure_c m)
```
4. For executable tests, use add_executable and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_executable(DiscreteDistributionTest src/Distribution.cpp src/Distribution.h src/DiscreteDistribution.cpp src/DiscreteDistribution.h src/Vector.cpp src/Vector.h src/Eigenvector.cpp src/Eigenvector.h src/Matrix.cpp src/Matrix.h src/Tensor.cpp src/Tensor.h Test/DiscreteDistributionTest.cpp)
	target_link_libraries(DiscreteDistributionTest util_c::util_c data_structure_c::data_structure_c m)
```

### Data files
1. Add data files to the cmake-build-debug folder.

### C++ files

1. If needed, comparator operators == and < should be implemented for map and set data structures.
```
    bool operator==(const Word &anotherWord) const{
        return (name == anotherWord.name);
    }
    bool operator<(const Word &anotherWord) const{
        return (name < anotherWord.name);
    }
```
2. Do not forget to comment each function.
```
	/**
 	* A constructor of Word class which gets a String name as an input and assigns to the name variable.
	*
	* @param _name String input.
 	*/
	Word::Word(const string &_name) {
```
3. Function names should follow caml case.
```
	int Word::charCount() const
```
4. Write getter and setter methods.
```
	string Word::getName() const
	void Word::setName(const string &_name)
```
5. Use catch.hpp for testing purposes. Add
```
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
```
line in only one of the test files. Add
```
#include "catch.hpp"
```
line in all test files. Example test file is given below:
```
TEST_CASE("DictionaryTest") {
    TxtDictionary lowerCaseDictionary = TxtDictionary("lowercase.txt", "turkish_misspellings.txt");
    TxtDictionary mixedCaseDictionary = TxtDictionary("mixedcase.txt", "turkish_misspellings.txt");
    TxtDictionary dictionary = TxtDictionary();
    SECTION("testSize"){
        REQUIRE(29 == lowerCaseDictionary.size());
        REQUIRE(58 == mixedCaseDictionary.size());
        REQUIRE(62113 == dictionary.size());
    }
    SECTION("testGetWord"){
        for (int i = 0; i < dictionary.size(); i++){
            REQUIRE_FALSE(nullptr == dictionary.getWord(i));
        }
    }
    SECTION("testLongestWordSize"){
        REQUIRE(1 == lowerCaseDictionary.longestWordSize());
        REQUIRE(1 == mixedCaseDictionary.longestWordSize());
        REQUIRE(21 == dictionary.longestWordSize());
    }
```
6. Enumerated types should be declared with enum class.
```
	enum class Pos {
		ADJECTIVE,
		NOUN,
		VERB,
		ADVERB,
```
7. Every header file should start with
```
	#ifndef MATH_DISTRIBUTION_H
	#define MATH_DISTRIBUTION_H
```
and end with
```
	#endif //MATH_DISTRIBUTION_H
```
8. Do not forget to use const expression for parameters, if they will not be changed in the function.
```
	void Word::setName(const string &_name);
```
9. Do not forget to use const expression for methods, which do not modify any class attribute. Also use [[dodiscard]]
```
	[[nodiscard]] bool isPunctuation() const;
```
10. Use xmlparser package for parsing xml files.
```
    auto* doc = new XmlDocument("test.xml");
    doc->parse();
    XmlElement* root = doc->getFirstChild();
    XmlElement* firstChild = root->getFirstChild();
```
11. Data structures: Use map for hash map, unordered_map for linked hash map, vector for array list, unordered_set for hash set
