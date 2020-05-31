For Developers
============

You can also see [Java](https://github.com/starlangsoftware/TurkishWordNet), [Python](https://github.com/starlangsoftware/TurkishWordNet-Py), or [C#](https://github.com/starlangsoftware/TurkishWordNet-CS) repository.

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

Türkçe WordNet KeNet'i yüklemek için

	WordNet a = new WordNet();

Belirli bir WordNet'i yüklemek için

	WordNet domain = new WordNet("domain_wordnet.xml", new Locale("tr"));

Tüm synsetleri getirmek için

	Collection<SynSet> synSetList()

Belirli bir synseti getirmek için

	SynSet getSynSetWithId(String synSetId)

Belirli bir kelimenin tüm anlamlarını (Synsetlerini) getirmek için

	ArrayList<SynSet> getSynSetsWithLiteral(String literal)

## SynSet

Bir synsetin eş anlamlı literallerini bulmak için Synonym elde edilir.

	Synonym getSynonym()
	
Bir synsetin içindeki Relation'ları indeks bazlı elde etmek için

	Relation getRelation(int index)

metodu ile bulunur. Örneğin, bir synsetin içindeki tüm ilişkiler

	for (int i = 0; i < synset.relationSize(); i++){
		relation = synset.getRelation(i);
		...
	}

## Synonym

Synonym'in içindeki literaller indeks bazlı

	Literal getLiteral(int index)

metodu ile bulunur. Örneğin, bir synonym içindeki tüm literaller

	for (int i = 0; i < synonym.literalSize(); i++){
		literal = synonym.getLiteral(i);
		...
	}
