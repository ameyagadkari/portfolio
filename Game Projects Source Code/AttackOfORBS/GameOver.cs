using UnityEngine;
using System.Collections;

public class GameOver: MonoBehaviour
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
				GUI.Label (new Rect (Screen.width / 2 - 400, Screen.height / 2 - 100, 800, 100), "GAMEOVER");
				GUI.Label (new Rect (Screen.width / 2 - 400, Screen.height / 2 - 50, 800, 100), "Your Score: " + PlayerPrefs.GetFloat ("TimeSurvied") + " secs");
				if (ModeSelect.chooseScript) {
						GUI.Label (new Rect (Screen.width / 2 - 400, Screen.height / 2, 800, 100), "High Score: " + PlayerPrefs.GetFloat ("HighestTimeSurvied_n") + " secs");
				} else {
						GUI.Label (new Rect (Screen.width / 2 - 400, Screen.height / 2, 800, 100), "High Score: " + PlayerPrefs.GetFloat ("HighestTimeSurvied_i") + " secs");
				}

				if (GUI.Button (new Rect (Screen.width / 2 - 100, Screen.height / 2 - 150, 200, 50), "BACK TO MAIN MENU") || Input.GetKeyDown ("escape")) {
						Application.LoadLevel (0);	
				}
		}
}
