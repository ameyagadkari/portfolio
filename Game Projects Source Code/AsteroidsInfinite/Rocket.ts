module AsteroidsReboot {
    export class Rocket extends Phaser.Sprite {
        game: Phaser.Game;
        movementSpeed: number;
        turnSpeed: number;
        cursors: Phaser.CursorKeys;
        thrust: Phaser.Sound;
        constructor(game, x, y, thrust) {
            this.game = game;
            this.thrust = thrust;
            this.cursors = this.game.input.keyboard.createCursorKeys();
            this.cursors.up.onDown.add(this.isThrusting, this);
            this.cursors.up.onUp.add(this.isNotThrusting, this);

            this.movementSpeed = 200;
            this.turnSpeed = 300;

            super(game, x, y, "rocketnotail");
            this.scale.setTo(0.4, 0.4);
            this.anchor.set(0.5, 0.5);
            this.pivot.set(0.5, 0.5);
            this.rotation = -Math.PI / 2;
            this.game.physics.enable(this, Phaser.Physics.ARCADE);
            this.body.drag.set(100);
            this.body.maxVelocity.set(200);


        }
        update() {
            this.game.world.wrap(this, 16);
            this.body.acceleration.set(0);
            this.body.angularVelocity = 0;
            if (this.cursors.up.isDown) {
                this.game.physics.arcade.accelerationFromRotation(this.rotation, this.movementSpeed, this.body.acceleration);
            }

            if (this.cursors.left.isDown) {
                this.body.angularVelocity = -this.turnSpeed;
            }
            else if (this.cursors.right.isDown) {
                this.body.angularVelocity = this.turnSpeed;
            }
        }
        isThrusting() {
            this.loadTexture("rockettail");
            this.thrust.play();
        }
        isNotThrusting() {
            this.loadTexture("rocketnotail");
            this.thrust.stop();
        }
    }
}