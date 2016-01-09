using UnityEngine;
using System.Collections;

public class Manager : MonoBehaviour
{

		public GUISkin mySkin;
		// Use this for initialization
		void Start ()
		{

		}
	
		// Update is called once per frame
		void Update ()
		{
		}

		void OnGUI ()
		{
				GUI.skin = mySkin;
				GUI.Label (new Rect (Screen.width / 2 - 275, 0, 550, 100), "Attack Of the ORBS-A Survival Game");
				GUI.Label (new Rect (Screen.width / 2 - 800, 100, 1600, 400), "Game Objective:Kill ORBS Using Your Magic Glow Wand\n\n" +
						"NORMAL MODE:Match the COLOR Of the WAND to that of the ORB to DESTROY IT\n" +
						"INSANE MODE:Combine the TWO PRIMARY ALTERNATING COLOR of an orb to its SECONDARY COLOR and use that COLOR WAND to DESTROY IT(R+G=YELLOW,G+B=CYAN,B+R=MAGENTA)\n\n" +
						"Change the COLOR using MOUSE BUTTON ONE(LEFT CLICK)\n" +
						"If the ORB Hits you, you LOSE 2 HEALTH POINTS\n" +
						"If you hit the ORB, you GAIN a HEALTH POINT\n" +
						"WASD\\ARROW KEYS to MOVE around,SPACEBAR to JUMP and MOUSE to LOOK AROUND\n" +
						"SURVIVE as LONG as you CAN");
				GUI.Box (new Rect (Screen.width / 2 - 100, Screen.height / 2 + 50, 200, 150), "START GAME\nIN");
				if (GUI.Button (new Rect (Screen.width / 2 - 100, Screen.height / 2 + 100, 200, 50), "NORMAL MODE")) {
						ModeSelect.chooseScript = true;
						Application.LoadLevel (1);
				}
				if (GUI.Button (new Rect (Screen.width / 2 - 100, Screen.height / 2 + 150, 200, 50), "INSANE MODE")) {
						ModeSelect.chooseScript = false;
						Application.LoadLevel (1);
				}
				if (GUI.Button (new Rect (Screen.width / 2 - 100, Screen.height / 2 + 200, 200, 50), "QUIT")) {
						Application.Quit ();
				}
		}

}
