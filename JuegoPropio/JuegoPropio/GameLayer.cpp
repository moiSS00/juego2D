#include "GameLayer.h"

#include "Gota.h"
#include "Hielo.h"
#include "Nube.h"

#include "ZombieBasico.h"
#include "ZombieRapido.h"
#include "ZombieFuerte.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) { //llama al constructor del padre : Layer(renderer)

	// Prepraramos el tutorial inicial
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	// Inicializamos los audios
	audioBackground = new Audio("res/musica_ambiente.wav", true);
	audioGanar = new Audio("res/ganar.wav", false);
	audioPerder = new Audio("res/perder.wav", false);
	audioMatarPlanta = new Audio("res/matarPlanta.wav", false);
	audioMatarZombie = new Audio("res/matarZombie.wav", false);

	// Ponemos la musica de fondo
	audioBackground->play();

	init();
}

void GameLayer::init() {

	// Numero incial de cerebros 
	cerebros = 100;

	// Fondo
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	// Marcador de cerebros
	backgroundContadorCerebros = new Actor("res/contadorCerebros.png", WIDTH * 0.07, HEIGHT * 0.10, 69, 65, game);
	textCerebros = new Text("", WIDTH * 0.09, HEIGHT * 0.19, 0, 0, 0, game);
	textCerebros->content = to_string(cerebros);

	// Selector de zombies
	backgroundSelector = new Actor("res/selector.png", WIDTH * 0.33, HEIGHT * 0.10, 179, 66, game);
	botonZombieBasico = new Actor("res/iconoZombieBasico.png", WIDTH * 0.22, HEIGHT * 0.10, 35, 52, game);
	botonZombieRapido = new Actor("res/iconoZombieRapido.png", WIDTH * 0.32, HEIGHT * 0.10, 35, 52, game);
	botonZombieFuerte = new Actor("res/iconoZombieFuerte.png", WIDTH * 0.42, HEIGHT * 0.10, 35, 52, game);
	textCosteZombieBasico = new Text(to_string(costeZombieBasico), WIDTH * 0.235, HEIGHT * 0.19, 255, 255, 255, game);
	textCosteZombieRapido = new Text(to_string(costeZombieRapido), WIDTH * 0.34, HEIGHT * 0.19, 255, 255, 255, game);
	textCosteZombieFuerte = new Text(to_string(costeZombieFuerte), WIDTH * 0.44, HEIGHT * 0.19, 255, 255, 255, game);

	// Bot�n de pausa
	botonPausa = new Actor("res/btnPausa.png", WIDTH * 0.93, HEIGHT * 0.10, 69, 65, game);

	// Indicadores del zombie seleccionado
	clickedZombieBasico = false; 
	clickedZombieRapido = false; 
	clickedZombieFuerte = false; 

	// Vaciar listas para poder reinicar el juego
	plataformas.clear();
	enemies.clear(); 
	zombies.clear(); 
	projectiles.clear();

	// Cargar nivel
	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::update() {

	// Si estamos en pausa no actualzamos
	if (pause) {
		return;
	}

	// Si le hemos dado al bot�n de pausa
	if (controlPause) {
		message = new Actor("res/pausa.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH * 0.45, HEIGHT * 0.45, game);
		pause = true;
	}

	// El jugador gana cuando no quedan enemigos
	if (enemies.size() == 0) {
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
			game->goToMenuLayer(); 
			audioBackground->play(); 
		}
		else {
			message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH * 0.7, HEIGHT * 0.5, game);
			pause = true;
			audioGanar->play();
		}
		init();
	}

	// El jugador pierde cuando no queda ningun zombie en el campo, queda algun enemigo y tampoco tiene puntos para comprar zombies
	if (zombies.size() == 0 && enemies.size() > 0 && cerebros < costeZombieBasico) {
		message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH * 0.7, HEIGHT * 0.5, game);
		pause = true;
		audioPerder->play(); 
		init();
	}
	
	// Actualizamos a los enemigos
	for (auto const& enemy : enemies) {
		enemy->update();
	}

	// Actualizamos a los zombies 
	for (auto const& zombie : zombies) {
		zombie->update();
	}

	// Actualizamos a los proyectiles
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	// Una planta empezar� a disparar si tiene alg�n zombie en su misma fila
	for (auto const& enemy : enemies) {
		bool shoot = false; 
		for (auto const& zombie : zombies) {
			if (zombie->y +10 == enemy->y && enemy->state == game->stateMoving) {
				shoot = true;
				break;
			}
		}
		if (shoot) {
			Projectile* projectile; 
			projectile = enemy->attack();
			if (projectile != NULL) {
				projectiles.push_back(projectile);
			}
		}
	}
	
	// Colisiones

	list<Enemy*> deleteEnemies;
	list<Zombie*> deleteZombies;
	list<Projectile*> deleteProjectiles;

	// Colision Zombie <-> Enemigo
	for (auto const& zombie : zombies) {
		for (auto const& enemy : enemies) {
			if (zombie->isOverlap(enemy) // Hay overlap
				&& zombie->containsPoint(enemy->x + 5, enemy->y)) { // El zombie y el enemigo estan en la misma fila
				bool ataque = zombie->attack();
				if (ataque) {
					enemy->loseLife(zombie->damage);
				}
			}
		}	
	}

	// Colisiones , Enemy <-> Projectile
	for (auto const& zombie : zombies) {
		for (auto const& projectile : projectiles) {
			if (zombie->isOverlap(projectile) // Hay overlap 
				&& zombie->state != game->stateDying && zombie->state != game->stateDead// El zombie no esta en estado "dying" o "dead"
				&& projectile->y == zombie->y + 10 && projectile->x <= zombie->x) { // Estan en la misma fila y el proyectil esta antes del zombie
				zombie->loseLife(projectile->damage); 
				if (zombie->state == game->stateDying) {
					audioMatarZombie->play();
				}
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

			}
		}
	}

	// Fase de eliminaci�n 

	// Los enemigos que esten en estado "dead" pasaran a eliminarse
	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
				cerebros += enemy->cerebrosDados;
				textCerebros->content = to_string(cerebros);
				audioMatarPlanta->play();
			}
		}
	}

	// Los proyectiles que no esten en pantalla se eliminan
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	// Se elimian los zombies que esten en estado "dead" o no esten en pantalla
	for (auto const& zombie : zombies) {
		if (zombie->state == game->stateDead || zombie->isInRender() == false) {
			bool eInList = std::find(deleteZombies.begin(),
				deleteZombies.end(),
				zombie) != deleteZombies.end();

			if (!eInList) {
				deleteZombies.push_back(zombie);
			}
		}
	}

	// Eliminamos enemigos
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	// Eliminamos zombies
	for (auto const& delZombie : deleteZombies) {
		zombies.remove(delZombie);
	}
	deleteZombies.clear();

	// Eliminamos proyectiles
	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {

	// Pintamos fondo
	background->draw();

	// Pintamos indicador de cerebros
	backgroundContadorCerebros->draw();
	textCerebros->draw();

	// Pintamos selector de zombies
	backgroundSelector->draw();
	botonZombieBasico->draw();
	botonZombieRapido->draw();
	botonZombieFuerte->draw(); 
	textCosteZombieBasico->draw();
	textCosteZombieRapido->draw();
	textCosteZombieFuerte->draw();

	// Pintamos bot�n de pausa
	botonPausa->draw();

	// Pintamos los enemigos
	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	// Pintamos los spawns de zombies
	for (auto const& plataforma : plataformas) {
		plataforma->draw();
	}

	// Pintar a los zombies / proyectiles por orden (ordenados por fila) para que no se pinten unos encimas de otros
	map<int, list<Actor*>> actoresFila;
	map<int, list<Actor*>>::iterator it;

	for (auto const& zombie : zombies) {
		actoresFila[zombie->y].push_back(zombie);
	}

	for (auto const& projectile : projectiles) {
		actoresFila[projectile->y].push_back(projectile);
	}

	for (it = actoresFila.begin(); it != actoresFila.end(); it++)
	{
		for (auto const& actor : it->second) {
			actor->draw();
		}
	}
	actoresFila.clear();

	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		// Cambio autom�tico de input
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}

		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}

	}

	//procesar controles

	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Se creara un zombie espec�fico en funci�n del zombie seleccionado
	for (auto const& plataforma : plataformas) {
		if (plataforma->clicked) { // Si se dio click a una plataforma
			if (clickedZombieBasico && cerebros >= costeZombieBasico) { // Si se quiere un zombie b�sico
				Zombie* zombie = new ZombieBasico(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros -= costeZombieBasico;
				textCerebros->content = to_string(cerebros);
			}
			if (clickedZombieRapido && cerebros >= costeZombieRapido) { // Si se quiere un zombie r�pido
				Zombie* zombie = new ZombieRapido(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros -= costeZombieRapido;
				textCerebros->content = to_string(cerebros);
			}
			if (clickedZombieFuerte && cerebros >= costeZombieFuerte) { // Si se quiere un zombie fuerte
				Zombie* zombie = new ZombieFuerte(plataforma->x, plataforma->y - 20, game);
				zombies.push_back(zombie);
				cerebros -= costeZombieFuerte;
				textCerebros->content = to_string(cerebros);
			}
			plataforma->clicked = false;
		}
	}
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
			case SDLK_ESCAPE:
				game->loopActive = false;
				break;
			case SDLK_1:
				game->scale();
				break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {}
	}
}

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificaci�n de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		controlPause = false;
		if (botonZombieBasico->containsPoint(motionX, motionY)) { // Bot�n zombie b�sico activado
			clickedZombieBasico = true; 
			clickedZombieRapido = false; 
			clickedZombieFuerte = false; 
		}

		if (botonZombieRapido->containsPoint(motionX, motionY)) { // Bot�n zombie r�pido activado
			clickedZombieRapido = true; 
			clickedZombieBasico = false; 
			clickedZombieFuerte = false;
		}

		if (botonZombieFuerte->containsPoint(motionX, motionY)) { // Bot�n zombie fuerte activado
			clickedZombieFuerte = true;
			clickedZombieRapido = false;
			clickedZombieBasico = false;
		}

		if (botonPausa->containsPoint(motionX, motionY)) { // Bot�n pausa activado
			controlPause = true;
		}

		for (auto const& plataforma : plataformas) { // Comprobamos si se activ� alguna plataforma
			if (plataforma->containsPoint(motionX, motionY)) {
				plataforma->clicked = true; 
			}
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {


	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {

	}
}


void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por l�nea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			// Por car�cter (en cada l�nea)
			for (int j = 0; j < line.length(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 50 / 2 + j * 50; // x central
				float y = 46 + i * 46; // y suelo
				loadMapObject(character, x, y);
			}
			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'G': { // Gota
		Enemy* enemie = new Gota(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'H': { // Hielo
		Enemy* enemie = new Hielo(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'N': { // Nube
		Enemy* enemie = new Nube(x, y, game);
		enemies.push_back(enemie);
		break;
	}
	case 'Z': { // Plataforma zombie
		Actor* plataforma = new Actor("res/plataforma.png", x, y + 10, 32, 40, game); 
		plataformas.push_back(plataforma);
		break;
	}
	}
}

