module AsteroidsReboot {
    export class BattleScreenState extends Phaser.State {
        game: Phaser.Game;

        rocket: Rocket;
        rocketTween: Phaser.Tween;
        rocketSelector: number;
        playerBullets: PlayerBullet;
        spaceKey: Phaser.Key;
        isAnimationComplete: boolean;
        explosionAnimationSprite: Phaser.Sprite;
        explosionAnimation: Phaser.Animation;
        rocketExplosion: Phaser.Sound;
        modeSelector: number;

        lives: number;
        livesImage: Phaser.Image[];

        asteroids: Asteroids;
        numberOfBigAsteroids: number;
        spawnLocationSelector: boolean;

        gameStart: Phaser.Sound;
        backgroundMusic: Phaser.Sound;
        playerBulletSound: Phaser.Sound;
        thrust: Phaser.Sound;

        scoreText: Phaser.Text;
        score: number;
        isCollideActive: boolean;

        shootFrequency: number;

        ufoFollower: Ufo;
        enemyBulletsFollowerUfo: EnemyBullet;

        
        ufoDown: Ufo;
        ufoDownMovementTween: Phaser.Tween;
        ufoDownAlphaTween: Phaser.Tween;
        isUfoDownAlphaTweenActive: boolean;
        enemyBulletsDownUfo: EnemyBullet;

        ufoLeft: Ufo;
        ufoLeftMovementTween: Phaser.Tween;
        ufoLeftAlphaTween: Phaser.Tween;
        isUfoLeftAlphaTweenActive: boolean;
        enemyBulletsLeftUfo: EnemyBullet;

        ufoUp: Ufo;
        ufoUpMovementTween: Phaser.Tween;
        ufoUpAlphaTween: Phaser.Tween;
        isUfoUpAlphaTweenActive: boolean;
        enemyBulletsUpUfo: EnemyBullet;

        ufoRight: Ufo;
        ufoRightMovementTween: Phaser.Tween;
        ufoRightAlphaTween: Phaser.Tween;
        isUfoRightAlphaTweenActive: boolean;
        enemyBulletsRightUfo: EnemyBullet;
        
        constructor() {
            super();
        }
        init(game, rocketSelector, modeSelector) {
            this.game = game;
            this.rocketSelector = rocketSelector;
            this.modeSelector = modeSelector;
            this.numberOfBigAsteroids = 0;
            this.spawnLocationSelector = true;
            this.lives = 3;
            this.score = 0;
            this.isCollideActive = true;
            this.isUfoDownAlphaTweenActive = false;
            this.isUfoLeftAlphaTweenActive = false;
            this.isUfoUpAlphaTweenActive = false;
            this.isUfoRightAlphaTweenActive = false;
            this.isAnimationComplete = false;
            this.shootFrequency = 2;
        }
        preload() {
            this.game.load.image("background", "Graphics/BattleScreen/background.png");
            this.game.load.image("background", "Graphics/BattleScreen/background.png");
            this.game.load.image("rocketnotail", "Graphics/BattleScreen/PlayerSprites/rocket" + this.rocketSelector + "notail.png");
            this.game.load.image("rockettail", "Graphics/BattleScreen/PlayerSprites/rocket" + this.rocketSelector + "tail.png");
            this.game.load.image("rocketlives", "Graphics/BattleScreen/Lives/rocket" + this.rocketSelector + "lives.png");
            this.game.load.image("playerBullet", "Graphics/BattleScreen/playerbullet.png");
            this.game.load.spritesheet("explosion", "Graphics/BattleScreen/PlayerSprites/explosion" + this.rocketSelector + ".png", 224, 134, 9);

            this.game.load.image("asteroidBig", "Graphics/BattleScreen/Asteroids/asteroidBig.png");
            this.game.load.image("asteroidMedium", "Graphics/BattleScreen/Asteroids/asteroidMedium.png");
            this.game.load.image("asteroidSmall", "Graphics/BattleScreen/Asteroids/asteroidSmall.png");

            this.game.load.image("ufo", "Graphics/BattleScreen/ufo.png");
            this.game.load.image("enemyBullet", "Graphics/BattleScreen/enemybullet.png");


            this.game.load.audio("gameStart", "Sounds/BattleScreen/gameStart.wav");
            this.game.load.audio("backgroundMusic", "Sounds/BattleScreen/Fight-Or-Free.wav");
            this.game.load.audio("playerBulletSound", "Sounds/BattleScreen/playerBulletSound.wav");
            this.game.load.audio("thrust", "Sounds/BattleScreen/thrust.wav");
            this.game.load.audio("rocketExplosion", "Sounds/BattleScreen/rocketExplosion.wav");
        }
        create() {
            this.game.physics.startSystem(Phaser.Physics.ARCADE);
            var style = { font: "30px Arial", fontStyle: "bold", fill: "#00ffff", align: "center" };
            this.game.add.image(0, 0, "background");
            
            //music
            this.gameStart = this.game.add.audio("gameStart");
            this.gameStart.play();
            this.gameStart.onStop.addOnce(this.StartBackgroundMusic, this);
            this.backgroundMusic = this.game.add.audio("backgroundMusic", 0.2, true);
            this.playerBulletSound = this.game.add.audio("playerBulletSound");
            this.thrust = this.game.add.audio("thrust", 0.1, true);
            this.rocketExplosion = this.game.add.audio("rocketExplosion");
            //keyboard
            this.spaceKey = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
            this.spaceKey.onDown.add(this.PlayBulletSound, this);

            //lives and score
            this.livesImage = [this.game.add.image(this.game.width - 148 * 1 * 0.4, 0, "rocketlives"), this.game.add.image(this.game.width - 148 * 2 * 0.4, 0, "rocketlives"), this.game.add.image(this.game.width - 148 * 3 * 0.4, 0, "rocketlives")];
            for (var i = 0; i < 3; i++) {
                this.livesImage[i].scale.setTo(0.4, 0.4);
            }
            this.scoreText = this.game.add.text(0, 0, "Score: " + this.score.toString(), style);
            //rocket
            this.rocket = new Rocket(this.game, this.game.width / 2, this.game.height / 2, this.thrust);
            this.game.add.existing(this.rocket);
            this.rocketTween = this.game.add.tween(this.rocket).to({ alpha: 0.5 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.rocketTween.pause();
            this.explosionAnimationSprite = this.game.add.sprite(this.rocket.x, this.rocket.y, "explosion");
            this.explosionAnimation = this.explosionAnimationSprite.animations.add("explode");
            this.explosionAnimationSprite.kill();
            this.explosionAnimation.onComplete.add(this.changeIsAnimationComplete, this);
            //playerbullets
            this.playerBullets = new PlayerBullet(this.game, this.rocket);
            this.game.add.existing(this.playerBullets);
            //astroids
            this.asteroids = new Asteroids(this.game);
            this.game.add.existing(this.asteroids);

            if (this.modeSelector == 1) {
                //follower ufo
                this.ufoFollower = new Ufo(this.game, this.rocket.x, this.rocket.y + 250, this.rocket.rotation);
                this.game.add.existing(this.ufoFollower);
                this.ufoFollower.body.allowRotation = false;

                this.enemyBulletsFollowerUfo = new EnemyBullet(this.game, this.ufoFollower, this.shootFrequency);
                this.game.add.existing(this.enemyBulletsFollowerUfo);   
            }
            else {
                //down ufo
                this.ufoDown = new Ufo(this.game, 60, this.game.height - 60, -Math.PI / 2);
                this.game.add.existing(this.ufoDown);
                this.ufoDownMovementTween = this.game.add.tween(this.ufoDown).to({ x: this.game.width - 60 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoDownMovementTween.timeScale = 0.1;
                this.ufoDownAlphaTween = this.game.add.tween(this.ufoDown).to({ alpha: 0 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoDownAlphaTween.timeScale = 0.1;
                this.ufoDownAlphaTween.pause();
                this.game.time.events.loop(Phaser.Timer.SECOND * 5, this.changeUfoDownAlphaTweenActive, this);
                this.enemyBulletsDownUfo = new EnemyBullet(this.game, this.ufoDown, this.shootFrequency);
                this.game.add.existing(this.enemyBulletsDownUfo);
                //left ufo
                this.ufoLeft = new Ufo(this.game, 60, 60, 0);
                this.game.add.existing(this.ufoLeft);
                this.ufoLeftMovementTween = this.game.add.tween(this.ufoLeft).to({ y: this.game.height - 60 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoLeftMovementTween.timeScale = 0.1;
                this.ufoLeftAlphaTween = this.game.add.tween(this.ufoLeft).to({ alpha: 0 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoLeftAlphaTween.timeScale = 0.1;
                this.ufoLeftAlphaTween.pause();
                this.game.time.events.loop(Phaser.Timer.SECOND * 10, this.changeUfoLeftAlphaTweenActive, this);
                this.enemyBulletsLeftUfo = new EnemyBullet(this.game, this.ufoLeft, this.shootFrequency * 2);
                this.game.add.existing(this.enemyBulletsLeftUfo);
                //up ufo
                this.ufoUp = new Ufo(this.game, this.game.width - 60, 60, -3 * Math.PI / 2);
                this.game.add.existing(this.ufoUp);
                this.ufoUpMovementTween = this.game.add.tween(this.ufoUp).to({ x: 60 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoUpMovementTween.timeScale = 0.1;
                this.ufoUpAlphaTween = this.game.add.tween(this.ufoUp).to({ alpha: 0 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoUpAlphaTween.timeScale = 0.1;
                this.ufoUpAlphaTween.pause();
                this.game.time.events.loop(Phaser.Timer.SECOND * 15, this.changeUfoUpAlphaTweenActive, this);
                this.enemyBulletsUpUfo = new EnemyBullet(this.game, this.ufoUp, this.shootFrequency * 4);
                this.game.add.existing(this.enemyBulletsUpUfo);
                //rifht ufo
                this.ufoRight = new Ufo(this.game, this.game.width - 60, this.game.height - 60, Math.PI);
                this.game.add.existing(this.ufoRight);
                this.ufoRightMovementTween = this.game.add.tween(this.ufoRight).to({ y: 60 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoRightMovementTween.timeScale = 0.1;
                this.ufoRightAlphaTween = this.game.add.tween(this.ufoRight).to({ alpha: 0 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
                this.ufoRightAlphaTween.timeScale = 0.1;
                this.ufoRightAlphaTween.pause();
                this.game.time.events.loop(Phaser.Timer.SECOND * 20, this.changeUfoRightAlphaTweenActive, this);
                this.enemyBulletsRightUfo = new EnemyBullet(this.game, this.ufoRight, this.shootFrequency * 8);
                this.game.add.existing(this.enemyBulletsRightUfo);    
            }
        }
        update() {
            if (this.modeSelector == 1) {
                this.ufoFollower.rotation = this.game.physics.arcade.accelerateToObject(this.ufoFollower, this.rocket, 50, 200, 200);
            }
            if (!this.lives) {
                this.backgroundMusic.stop();
                this.game.state.start("GameoverScreenState", true, true, this.game, this.score);
            }
            if (!this.rocket.exists && this.isAnimationComplete) {
                this.isAnimationComplete = false;
                this.isCollideActive = false;
                this.livesImage[--this.lives].kill();
                this.rocket.reset(this.game.width / 2, this.game.height / 2);
                this.rocket.rotation = -Math.PI / 2;
                this.isCollideActive = false;
                this.rocketTween.resume();
                this.game.time.events.add(Phaser.Timer.SECOND * 5, this.changeIsCollideActive, this);
            }
            if (this.numberOfBigAsteroids < 4) {
                if (this.spawnLocationSelector) {
                    var x = this.game.rnd.between(100, this.rocket.x - 100);
                    var y = this.game.rnd.between(100, this.rocket.y - 100);
                    this.spawnLocationSelector = false;
                }
                else {
                    var x = this.game.rnd.between(this.rocket.x + 100, 900);
                    var y = this.game.rnd.between(this.rocket.y + 100, 800);
                    this.spawnLocationSelector = true;
                }
                this.asteroids.spawn(x, y, 0, 100, 40);
                this.numberOfBigAsteroids++;
            }
            this.game.physics.arcade.collide(this.asteroids, this.playerBullets, this.hitByBullet, null, this);
            if (this.isCollideActive) {
                this.game.physics.arcade.collide(this.rocket, this.asteroids, this.destroySpaceShip, null, this);
                if (this.modeSelector == 1) {
                    this.game.physics.arcade.collide(this.rocket, this.ufoFollower, this.killSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.enemyBulletsFollowerUfo, this.ufoKillSpaceShip, null, this);
                }
                else {
                    this.game.physics.arcade.collide(this.rocket, this.ufoDown, this.killSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.enemyBulletsDownUfo, this.ufoKillSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.ufoLeft, this.killSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.enemyBulletsLeftUfo, this.ufoKillSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.ufoUp, this.killSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.enemyBulletsUpUfo, this.ufoKillSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.ufoRight, this.killSpaceShip, null, this);
                    this.game.physics.arcade.collide(this.rocket, this.enemyBulletsRightUfo, this.ufoKillSpaceShip, null, this);
                }  
            }
        }
        StartBackgroundMusic() {
            this.backgroundMusic.play();
        }
        PlayBulletSound() {
            this.playerBulletSound.play();
        }
        changeIsAnimationComplete() {
            this.isAnimationComplete = true;
        }
        changeIsCollideActive() {
            this.isCollideActive = true;
            this.rocketTween.pause();
            this.rocket.alpha = 1;
        }
        //ufos alpha tweens
        changeUfoDownAlphaTweenActive() {
            if (!this.isUfoDownAlphaTweenActive) {
                this.isUfoDownAlphaTweenActive = true;
                this.ufoDownAlphaTween.resume();
            }
            else {
                this.isUfoDownAlphaTweenActive = false;
                this.ufoDownAlphaTween.pause();
                this.ufoDown.alpha = 1;
            }
        }
        changeUfoLeftAlphaTweenActive() {
            if (!this.isUfoLeftAlphaTweenActive) {
                this.isUfoLeftAlphaTweenActive = true;
                this.ufoLeftAlphaTween.resume();
            }
            else {
                this.isUfoLeftAlphaTweenActive = false;
                this.ufoLeftAlphaTween.pause();
                this.ufoLeft.alpha = 1;
            }
        }
        changeUfoUpAlphaTweenActive() {
            if (!this.isUfoUpAlphaTweenActive) {
                this.isUfoUpAlphaTweenActive = true;
                this.ufoUpAlphaTween.resume();
            }
            else {
                this.isUfoUpAlphaTweenActive = false;
                this.ufoUpAlphaTween.pause();
                this.ufoUp.alpha = 1;
            }
        }
        changeUfoRightAlphaTweenActive() {
            if (!this.isUfoRightAlphaTweenActive) {
                this.isUfoRightAlphaTweenActive = true;
                this.ufoRightAlphaTween.resume();
            }
            else {
                this.isUfoRightAlphaTweenActive = false;
                this.ufoRightAlphaTween.pause();
                this.ufoRight.alpha = 1;
            }
        }
        //event handler functiosn for collisons
        hitByBullet(asteroid, playerBullet) {
            playerBullet.kill();
            if (asteroid.key == "asteroidBig") {
                this.numberOfBigAsteroids--;
                this.score += 10;
                this.scoreText.text = "Score: " + this.score.toString();
            }
            else if (asteroid.key == "asteroidMedium") {
                this.score += 20;
                this.scoreText.text = "Score: " + this.score.toString();
            }
            else {
                this.score += 40;
                this.scoreText.text = "Score: " + this.score.toString();
            }
            this.asteroids.hit(asteroid);
        }
        killSpaceShip(rocket) {
            this.playDeathAnimation();
            rocket.kill();
        }
        ufoKillSpaceShip(rocket, enemyBullet) {
            this.playDeathAnimation();
            rocket.kill();
            enemyBullet.kill();
        }
        destroySpaceShip(rocket, asteroid) {
            this.playDeathAnimation();
            rocket.kill();
            this.asteroids.hit(asteroid);
            if (asteroid.key == "asteroidBig") {
                this.numberOfBigAsteroids--;
                this.score += 10;
                this.scoreText.text = "Score: " + this.score.toString();
            }
            else if (asteroid.key == "asteroidMedium") {
                this.score += 20;
                this.scoreText.text = "Score: " + this.score.toString();
            }
            else {
                this.score += 40;
                this.scoreText.text = "Score: " + this.score.toString();
            }
        }
        playDeathAnimation() {
            this.rocketExplosion.play();
            this.explosionAnimationSprite.reset(this.rocket.x, this.rocket.y);
            this.explosionAnimationSprite.scale = this.rocket.scale;
            this.explosionAnimationSprite.anchor = this.rocket.anchor;
            this.explosionAnimationSprite.pivot = this.rocket.pivot;
            this.explosionAnimationSprite.rotation = this.rocket.rotation;
            this.explosionAnimationSprite.animations.play("explode", 30, false, true);
        }
    }
}