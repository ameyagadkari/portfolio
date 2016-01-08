module AsteroidsReboot {
    export class Ufo extends Phaser.Sprite {
        game: Phaser.Game;
        movementSpeed: number;

        constructor(game, x, y, rotation) {
            this.game = game;
            this.movementSpeed = 50;

            super(game, x, y, "ufo");
            this.anchor.set(0.5, 0.5);
            this.pivot.set(0.5, 0.5);
            this.rotation = rotation;
            this.game.physics.enable(this, Phaser.Physics.ARCADE);
            this.body.immovable = true;
        }
    }
}