module AsteroidsReboot {
    export class EnemyBullet extends Phaser.Group {
        game: Phaser.Game;
        ufo: Ufo;
        enemyBulletLeft: Phaser.Sprite;
        enemyBulletRight: Phaser.Sprite;
        shootFrequency: number;
        leftOffset: Phaser.Point;
        rightOffset: Phaser.Point;
        bulletSpeed: number;
        bulletLifeSpan: number;
        constructor(game, ufo, shootFrequency) {
            this.game = game;
            this.ufo = ufo;
            this.shootFrequency = shootFrequency;
            this.bulletSpeed = 400;
            this.bulletLifeSpan = 2000;

            game.time.events.loop(Phaser.Timer.SECOND * this.shootFrequency, this.CreateBullet, this);

            super(this.game, this.game.world, "enemyBullets", false, true, Phaser.Physics.ARCADE);
        }
        update() {
            var enemyBullet = this.getFirstExists(false);
            if (enemyBullet) {
                this.remove(enemyBullet, true);
            }
        }
        CreateBullet() {
            var radius = 20 * Math.sqrt(10);
            var x = radius * (Math.cos(this.ufo.rotation));
            var y = radius * (Math.sin(this.ufo.rotation));
            this.leftOffset = new Phaser.Point(x, y);
            this.rightOffset = new Phaser.Point(x, y);
            this.leftOffset.rotate(this.ufo.anchor.x, this.ufo.anchor.y, -17.5, true, radius);
            this.rightOffset.rotate(this.ufo.anchor.x, this.ufo.anchor.y, 17.5, true, radius);

            this.enemyBulletLeft = this.create(this.ufo.x + this.leftOffset.x, this.ufo.y + this.leftOffset.y, "enemyBullet");
            this.enemyBulletLeft.anchor = this.ufo.anchor;
            this.enemyBulletLeft.pivot = this.ufo.pivot;
            this.enemyBulletLeft.lifespan = this.bulletLifeSpan;
            this.enemyBulletLeft.rotation = this.ufo.rotation;
            this.enemyBulletLeft.checkWorldBounds = true;
            this.enemyBulletLeft.outOfBoundsKill = true;
            this.add(this.enemyBulletLeft);

            this.enemyBulletRight = this.create(this.ufo.x + this.rightOffset.x, this.ufo.y + this.rightOffset.y, "enemyBullet");
            this.enemyBulletRight.anchor = this.ufo.anchor;
            this.enemyBulletRight.pivot = this.ufo.pivot;
            this.enemyBulletRight.lifespan = this.bulletLifeSpan;
            this.enemyBulletRight.rotation = this.ufo.rotation;
            this.enemyBulletRight.checkWorldBounds = true;
            this.enemyBulletRight.outOfBoundsKill = true;
            this.add(this.enemyBulletRight);

            this.game.physics.arcade.velocityFromRotation(this.ufo.rotation, this.bulletSpeed, this.enemyBulletLeft.body.velocity);
            this.game.physics.arcade.velocityFromRotation(this.ufo.rotation, this.bulletSpeed, this.enemyBulletRight.body.velocity);
        }
    }
}