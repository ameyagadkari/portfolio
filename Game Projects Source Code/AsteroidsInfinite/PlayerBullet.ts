module AsteroidsReboot {
    export class PlayerBullet extends Phaser.Group {
        game: Phaser.Game;
        spaceKey: Phaser.Key;
        rocket: Rocket;
        playerBullet: Phaser.Sprite;

        bulletSpeed: number;
        bulletLifeSpan: number;

        constructor(game, rocket) {
            this.game = game;
            this.rocket = rocket;
            this.spaceKey = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
            this.spaceKey.onDown.add(this.CreateBullet, this);

            this.bulletSpeed = 400;
            this.bulletLifeSpan = 1500;

            super(this.game, this.game.world, "playerBullets", false, true, Phaser.Physics.ARCADE);
        }
        update() {
            this.forEachExists(this.game.world.wrap, this.game.world);
            var playerBullet = this.getFirstExists(false);
            if (playerBullet) {
                this.remove(playerBullet, true);
            }
        }
        CreateBullet() {
            var radius = Math.sqrt(Math.pow(this.rocket.width / 2, 2) + Math.pow(this.rocket.height / 2, 2));
            var x = radius * (Math.cos(this.rocket.rotation));
            var y = radius * (Math.sin(this.rocket.rotation));

            this.playerBullet = this.create(this.rocket.x + x, this.rocket.y + y, "playerBullet");
            this.playerBullet.scale.setTo(0.6, 0.6);
            this.playerBullet.anchor = this.rocket.anchor;
            this.playerBullet.pivot = this.rocket.pivot;
            this.playerBullet.lifespan = this.bulletLifeSpan;
            this.playerBullet.rotation = this.rocket.rotation;
            this.add(this.playerBullet);

            this.game.physics.arcade.velocityFromRotation(this.rocket.rotation, this.bulletSpeed, this.playerBullet.body.velocity);
        }
    }
}