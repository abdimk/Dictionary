

<!-- markdownlint-disable MD033 -->
<!-- markdownlint-disable MD041 -->

<div align="center">
	<h1> C++ Dictionary using libCurl and Merriam Webster Api </h1>
	<a href="">
			<img src="https://github.com/abdimk/Dictionary/blob/main/Img/prg.png" width="700" height="450" alt="screenshot" />
		</a>
	<div>
		<a href="">
		<img src="https://shields.io/endpoint?url=https://badges.readysetplay.io/workflow/filiptibell/lune/ci.yaml" alt="CI status" />
		</a>
		<a href="">
			<img src="https://shields.io/endpoint?url=https://badges.readysetplay.io/workflow/filiptibell/lune/ci.yaml" alt="CI status" />
		</a>
		<a href="">
			<img src="https://shields.io/endpoint?url=https://badges.readysetplay.io/workflow/filiptibell/lune/release.yaml" alt="Release status" />
		</a>
		<a href="">
			<img src="https://img.shields.io/github/license/filiptibell/lune.svg?label=License&color=informational" alt="Current Lune library version" />
		</a>
	</div>
</div>


## Recent Updates 
- structure has been added.  logs=> [b496f276ba4e0f5ce26ab8b1910b7cfdeec307d6](https://github.com/abdimk/Dictionary/commit/b496f276ba4e0f5ce26ab8b1910b7cfdeec307d6)
- now token is stored in vars.txt file. logs=> [2c660ee6627a6241213709895d20211197cbc36d](https://github.com/abdimk/Dictionary/commit/2c660ee6627a6241213709895d20211197cbc36d)

- history(way to display the perivious query). logs=> [aa7864e1e4c65b60d039679e39758de1f48d55a7](https://github.com/abdimk/Dictionary/commit/aa7864e1e4c65b60d039679e39758de1f48d55a7)

---
## How does it work 
<p>  Here is how it works this is a cpp project that uses merriam webster api with json fetch meanings from the api and on the top of that it uses libcurl or curl for short to send a request to the api </p>


<p>It defines a <strong>Merriam</strong> struct that contains several methods for formatting and filtering strings, and for querying the Merriam-Webster Learner's Dictionary API. The main function creates an instance of the <strong>Merriam</strong> struct and repeatedly prompts the user to enter a word to search, then prints the definition of that word.</p>
---


## Project Overview

Merriam webster api read this [Merriam](https://dictionaryapi.com/account/example?)
<br>
Json for modern C++ [Json](https://github.com/nlohmann/json)
<br>
libcurl4-openssl-dev [libcurl4](https://github.com/curl/curl)



## Features

-  🌙 Fast and Reliable 
-   🧰 Related terms 
-   📚 Definition based on context 
-   🏡 Translations in to amharic[for future]
-   ✏️  integration with custom systems(bots, websites)[for future]


## Where do we start?

### ⚠️ You need to install curl library and libcurl4-openssl-dev else this project will fail on the build process 

## Installation

Assuming you have updated all the current packages let's install curl and libcurl4-openssl-dev 

```diff
 sudo apt-get update && sudo apt-get upgrade
```


```diff
 sudo apt-get install curl && sudo apt-get install libcurl4-openssl-dev
```

Then clone the github repo using

```diff
 git clone https://github.com/abdimk/Dictionary
```
Head to the repository

```diff
 cd Dictionary
```

Remove the pirvious build and build it again using make
```diff
 make clean && make
```

Run the code
You always need to be /Dictionary directory to run the code don't go to /Dictionary/bin 
```diff
 bin/main
```


## Credits 

<strong>Arash Nemat Zadeh</strong>!
