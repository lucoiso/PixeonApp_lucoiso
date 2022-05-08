# PixeonApp

App developed for Pixeon Challenge. The objective is to create a Image Viewer app using Qt Creator.

![image](https://user-images.githubusercontent.com/77353979/167266484-7194550e-636b-4d04-996b-907ea56d189f.png)

## Report (PT-BR)

**Metodologia utilizada:**
* Desenvolvimento de features por etapas, simulando mini sprints da metodologia scrum: Desenvolvi features progressivamente, implementando uma funcionalidade por vez e por fim, realizei ajustes e modificações para otimização das mesmas.

**Dificuldades encontradas:**
* O fato de não ter utilizado o Qt Creator por um bom tempo me exigiu algumas pesquisas para APIs que foram utilizadas.
* Por alguma razão, minhas tentativas de multithreading falharam e não descobri o motivo nas tentativas. Tentei utilizar QThread, std::thread e até criar um novo QObject para chamar uma função em uma thread separada, mas abort() era sempre chamado ao iniciar a iteração nos pixels. O multithreading seria implementado para evitar o congelamento da GUI ao modificar uma imagem muito grande.

**Técnicas utilizadas:**
* Utilização de macros para evitar repetição
* Utilização de features de C++ moderno como lambdas e delegates como parametro
* Utilização de prints via qDebug()

**Possíveis melhorias futuras:**
* Melhorias no visual
* Mais opções em menu de janela
* Mais opções em menu de gerenciamento de imagem
* Multithreading

**Avaliação do resultado:**
* Acredito que alcancei os objetivos propostos de forma simples e prática. O aplicativo, além de funcional, possui fácil manutenção e visibilidade.
