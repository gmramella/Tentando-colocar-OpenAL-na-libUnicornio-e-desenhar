# Tentando colocar OpenAL na libUnicornio e desenhar

## Como criar um projeto com OpenAL

* Instalar cmake usando .msi

* Clonar https://github.com/kcat/openal-soft

* Executar cmake .. na pasta build

* Abrir .sln criado na pasta build

* Depurar para criar uma pasta Debug

* Copiar arquivos OpenAL32.dll e OpenAL32.lib

* Na pasta do .sln do HelloOpenAL:

	* colocar um audio .wav

	* copiar pasta openal-soft-master\include

	* criar pasta lib e colocar OpenAL32.lib

* Colocar OpenAL32.dll na pasta com mesmo nome do projeto (que tem o .vcxproj)

* Criar o arquivo da função main

* Clicar no projeto no gerenciador de soluções > Alt + Enter:

	* C/C++ > Additional Include Directories: ../include;%(AdditionalIncludeDirectories)

	* Linker > General > Additional Library Directories: ../lib/;%(AdditionalLibraryDirectories)

	* Linker > Input > Additional Dependencies: ../lib/OpenAL32.lib;%(AdditionalDependencies)

## HelloOpenAL: exemplo de OpenAL no Visual Studio

* Para funcionar:

	* certifique-se de que esteja em Debug x86

## Funcionando1Musica: exemplo de OpenAL na libUnicornio

* É apenas um grande copia e cola do HelloOpenAL na libUnicornio, com a diferença que não adianta ter printf porque não tem console

* Precisa fazer funcionar com garantia 2+ músicas se quiser tocar 2+ sons simultaneamente

* Para funcionar:

	* compilar para criar uma pasta bin e colar arquivos da pasta bin de algum projeto da libUnicornio nesta pasta criada
	
	* adicionar OpenAL32.dll nesta pasta (disponibilizei junto aos projetos)
	
	* trocar .. por . na linha 17 do main.cpp

## Gravity: tentativa de mostrar na libUnicornio a onda sonora da música que estiver tocando

* Para funcionar:

	* compilar para criar uma pasta bin e colar arquivos da pasta bin de algum projeto da libUnicornio nesta pasta criada
	
	* adicionar OpenAL32.dll, libfftw3-3.dll e arial.ttf nesta pasta (disponibilizei junto aos projetos)
	
	* criar pastas Musics (onde vão as músicas usadas) e Files dentro da pasta bin
	
	* trocar ./Musics por ./bin/Musics nas linhas 50-63 do main.cpp
	
	* trocar ./Files por ./bin/Files nas linhas 96, 113, 122, 141 e 150 do AudioManager.h e 62 do Utils.cpp

* Referências:

	* https://www.youtube.com/watch?v=CMyG4hsKCJo
	
	* https://www.youtube.com/playlist?list=PLT5_DQAJJLh-ogHjHcLtFYMQy7SkZ7-3i
