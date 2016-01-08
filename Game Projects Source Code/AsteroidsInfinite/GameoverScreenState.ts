module AsteroidsReboot {
    export class GameoverScreenState extends Phaser.State {
        game: Phaser.Game;
        music: Phaser.Sound;
        scoreText: Phaser.Text;
        score: number;
        constructor() {
            super();
        }
        init(game, score) {
            this.game = game;
            this.score = score;
        }
        preload() {
            this.game.load.image("background", "Graphics/GameoverScreen/background.png");
            this.game.load.audio("backgroundMusic", "Sounds/GameoverScreen/gameover.wav");
        }
        create() {
            var style = { font: "60px Arial", fontStyle: "bold", fill: "#ffff00", align: "center" };
            this.game.add.image(0, 0, "background");
            this.scoreText = this.game.add.text(256, 660, "Your Score: " + this.score.toString(), style);
            this.input.onTap.addOnce(this.TitleClicked, this);
            this.music = this.game.add.audio("backgroundMusic");
            this.music.play();
        }
        TitleClicked() {
            this.game.state.start("TitleScreenState", true, true, this.game);
        }
    }
}