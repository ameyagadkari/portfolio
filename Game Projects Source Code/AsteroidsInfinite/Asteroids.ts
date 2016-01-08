module AsteroidsReboot {
    export class Asteroids extends Phaser.Group {
        game: Phaser.Game;
        asteroid: Phaser.Sprite;
        asteroidSizes: string[];
        constructor(game) {
            this.game = game;
            this.asteroidSizes = ["asteroidBig", "asteroidMedium", "asteroidSmall"];
            super(this.game, this.game.world, "asteroids", false, true, Phaser.Physics.ARCADE);
        }
        update() {
            this.forEachExists(this.game.world.wrap, this.game.world);
            var asteroid = this.getFirstExists(false);
            if (asteroid) {
                this.remove(asteroid, true);
            }
        }
        spawn(x, y, size, speed, rotate) {
            this.asteroid = this.create(x, y, this.asteroidSizes[size]);
            this.asteroid.scale.set(0.4);
            this.asteroid.anchor.set(0.5);
            this.asteroid.body.velocity.x = this.game.rnd.integerInRange(-speed, speed);
            this.asteroid.body.velocity.y = this.game.rnd.integerInRange(-speed, speed);
            this.asteroid.body.angularVelocity = rotate;
            this.add(this.asteroid);
        }
        hit(asteroid) {
            if (asteroid.key == "asteroidBig") {
                this.spawn(asteroid.x, asteroid.y, 1, asteroid.body.speed * 1.5, asteroid.body.angularVelocity * 1.5);
                this.spawn(asteroid.x, asteroid.y, 1, asteroid.body.speed * 1.5, asteroid.body.angularVelocity * 1.5);
                asteroid.kill();
            }
            else if (asteroid.key == "asteroidMedium") {
                this.spawn(asteroid.x, asteroid.y, 2, asteroid.body.speed * 1.5, asteroid.body.angularVelocity * 1.5);
                this.spawn(asteroid.x, asteroid.y, 2, asteroid.body.speed * 1.5, asteroid.body.angularVelocity * 1.5);
                this.spawn(asteroid.x, asteroid.y, 2, asteroid.body.speed * 1.5, asteroid.body.angularVelocity * 1.5);
                asteroid.kill();
            }
            else {
                asteroid.kill();
            }
        }
    }
}