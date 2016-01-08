module AsteroidsReboot {
    export class TitleScreenState extends Phaser.State {
        game: Phaser.Game;
        rocketSelector: number = 1;
        rocket1: Phaser.Image;
        rocket2: Phaser.Image;
        rocket3: Phaser.Image;
        music: Phaser.Sound;
        leftArrow: Phaser.Button;
        rightArrow: Phaser.Button;
        start: Phaser.Button;
        pacStroid: Phaser.Button;
        extreme: Phaser.Button;
        leftArrowTween: Phaser.Tween;
        rightArrowTween: Phaser.Tween;
        startTween: Phaser.Tween;
        pacStroidTween: Phaser.Tween;
        extremeTween: Phaser.Tween;
        constructor() {
            super();
        }
        init(game) {
            this.game = game;
        }

        preload() {
            this.game.load.image("background", "Graphics/TitleScreen/background.png");
            this.game.load.image("rocket1", "Graphics/TitleScreen/rocket1.png");
            this.game.load.image("rocket2", "Graphics/TitleScreen/rocket2.png");
            this.game.load.image("rocket3", "Graphics/TitleScreen/rocket3.png");
            this.game.load.image("leftArrow", "Graphics/TitleScreen/leftArrow.png");
            this.game.load.image("rightArrow", "Graphics/TitleScreen/rightArrow.png");
            this.game.load.image("pacStroid", "Graphics/TitleScreen/pacStroid.png");
            this.game.load.image("extreme", "Graphics/TitleScreen/extreme.png");
            this.game.load.image("start", "Graphics/TitleScreen/start.png");
            this.game.load.audio("backgroundMusic", "Sounds/TitleScreen/TheChase.wav");
        }
        create() {
            var style1 = { font: "20px Arial", fontStyle: "bold", fill: "#00ff00", align: "center" };
            var style2 = { font: "16px Arial", fill: "#00ff00", align: "center" };
            this.game.add.image(0, 0, "background");


            this.leftArrow = this.game.add.button(this.game.width / 2 - 294, this.game.height / 2 + 38 + 34, "leftArrow", this.ChangeRocketLeft, this);
            this.leftArrow.anchor.setTo(0.5, 0.5);
            this.leftArrow.onInputOver.add(this.EnableLeftTween, this);
            this.leftArrow.onInputOut.add(this.DisableLeftTween, this);
            this.leftArrowTween = this.game.add.tween(this.leftArrow.scale).to({ x: 0.9, y: 0.9 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.leftArrowTween.pause();

            this.rightArrow = this.game.add.button(this.game.width / 2 + 294, this.game.height / 2 + 38 + 34, "rightArrow", this.ChangeRocketRight, this);
            this.rightArrow.anchor.setTo(0.5, 0.5);
            this.rightArrow.onInputOver.add(this.EnableRightTween, this);
            this.rightArrow.onInputOut.add(this.DisableRightTween, this);
            this.rightArrowTween = this.game.add.tween(this.rightArrow.scale).to({ x: 0.9, y: 0.9 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.rightArrowTween.pause();

            this.start = this.game.add.button(this.game.width / 2, this.game.height / 2 + 354, "start", this.ChangeState, this);
            this.start.anchor.setTo(0.5, 0.5);
            this.start.onInputOver.add(this.EnableStartTween, this);
            this.start.onInputOut.add(this.DisableStartTween, this);
            this.startTween = this.game.add.tween(this.start.scale).to({ x: 0.9, y: 0.9 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.startTween.pause();

            this.pacStroid = this.game.add.button(this.game.width / 2 - 204, this.game.height / 2 + 354, "pacStroid", this.startPacStroids, this);
            this.pacStroid.kill();
            this.pacStroid.anchor.setTo(0.5, 0.5);
            this.pacStroid.onInputOver.add(this.EnablePacStroidTween, this);
            this.pacStroid.onInputOut.add(this.DisablePacStroidTween, this);
            this.pacStroidTween = this.game.add.tween(this.pacStroid.scale).to({ x: 0.9, y: 0.9 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.pacStroidTween.pause();

            this.extreme = this.game.add.button(this.game.width / 2 - 204, this.game.height / 2 + 354, "extreme", this.startExtreme, this);
            this.extreme.kill();
            this.extreme.anchor.setTo(0.5, 0.5);
            this.extreme.onInputOver.add(this.EnableExtremeTween, this);
            this.extreme.onInputOut.add(this.DisableExtremeTween, this);
            this.extremeTween = this.game.add.tween(this.extreme.scale).to({ x: 0.9, y: 0.9 }, 0, Phaser.Easing.power4, true, 0, Number.MAX_VALUE, true);
            this.extremeTween.pause();

            this.game.add.text(10, this.game.height / 2 + 190, "INSTRUCTIONS:", style1);
            this.game.add.text(30, this.game.height / 2 + 220, "Left/Right: Rotate", style2);
            this.game.add.text(30, this.game.height / 2 + 240, "Up: Thrust", style2);
            this.game.add.text(30, this.game.height / 2 + 260, "Spacebar: Shoot", style2);

            this.rocket1 = this.game.add.image(this.game.width / 2 - 145, this.game.height / 2 - 76, "rocket1");
            this.rocket2 = this.game.add.image(this.game.width / 2 - 145, this.game.height / 2 - 76, "rocket2");
            this.rocket3 = this.game.add.image(this.game.width / 2 - 145, this.game.height / 2 - 76, "rocket3");
            this.rocket2.visible = false;
            this.rocket3.visible = false;

            this.music = this.game.add.audio("backgroundMusic", 1.0, true);
            this.music.play();
        }
        ChangeRocketLeft() {
            if (this.rocket1.visible) {
                this.rocket1.visible = false;
                this.rocket3.visible = true;
                this.rocketSelector = 3;
            }
            else if (this.rocket2.visible) {
                this.rocket2.visible = false;
                this.rocket1.visible = true;
                this.rocketSelector = 1;
            }
            else {
                this.rocket3.visible = false;
                this.rocket2.visible = true;
                this.rocketSelector = 2;
            }
        }
        ChangeRocketRight() {
            if (this.rocket1.visible) {
                this.rocket1.visible = false;
                this.rocket2.visible = true;
                this.rocketSelector = 2;
            }
            else if (this.rocket2.visible) {
                this.rocket2.visible = false;
                this.rocket3.visible = true;
                this.rocketSelector = 3;
            }
            else {
                this.rocket3.visible = false;
                this.rocket1.visible = true;
                this.rocketSelector = 1;
            }
        }
        EnableLeftTween() {
            this.leftArrowTween.resume();
        }
        DisableLeftTween() {
            this.leftArrowTween.pause();
            this.leftArrow.scale.set(1.0, 1.0);
        }
        EnableRightTween() {
            this.rightArrowTween.resume();
        }
        DisableRightTween() {
            this.rightArrowTween.pause();
            this.rightArrow.scale.set(1.0, 1.0);
        }
        EnableStartTween() {
            this.startTween.resume();
        }
        DisableStartTween() {
            this.startTween.pause();
            this.start.scale.set(1.0, 1.0);
        }
        EnablePacStroidTween() {
            this.pacStroidTween.resume();
        }
        DisablePacStroidTween() {
            this.pacStroidTween.pause();
            this.pacStroid.scale.set(1.0, 1.0);
        }
        EnableExtremeTween() {
            this.extremeTween.resume();
        }
        DisableExtremeTween() {
            this.extremeTween.pause();
            this.extreme.scale.set(1.0, 1.0);
        }
        ChangeState() {
            this.start.kill();
            this.pacStroid.reset(this.game.width / 2 - 204, this.game.height / 2 + 354);
            this.extreme.reset(this.game.width / 2 + 204, this.game.height / 2 + 354);
        }
        startPacStroids() {
            this.music.stop();
            this.game.state.start("BattleScreenState", true, true, this.game, this.rocketSelector, 1);
        }
        startExtreme() {
            this.music.stop();
            this.game.state.start("BattleScreenState", true, true, this.game, this.rocketSelector, 2);
        }

    }
}