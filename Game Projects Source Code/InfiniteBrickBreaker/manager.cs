using UnityEngine;
using System.Collections;

public class manager : MonoBehaviour
{
		int score = 0;
		GUIText GUI_score, GUI_highscore;
		public GameObject brickPrefab;
		ArrayList bricks;
		public GUISkin mySkin;
		int highscore;
		// Use this for initialization
		void Start ()
		{
				GUI_score = GameObject.Find ("GUI score").GetComponent<GUIText> ();
				GUI_highscore = GameObject.Find ("GUI highscore").GetComponent<GUIText> ();
				spawnBrick ();
				bricks = new ArrayList ();
				highscore = PlayerPrefs.GetInt ("High Score");
		}
	
		// Update is called once per frame
		void Update ()
		{
		}

		void FixedUpdate ()
		{
				if (bricks.Count < 20) {
						spawnBrick ();
				}

		
		}

		public void diplayHighScore ()
		{
				if (score > highscore) {
						PlayerPrefs.SetInt ("High Score", score);
						GUI_highscore.text = "HIGH SCORE: " + score;
				} else {
						GUI_highscore.text = "HIGH SCORE: " + highscore;
				}
			
		}

		public void populateLevel (string name)
		{
				bricks.Add (name);
		}

		public void removeBrick (string name)
		{
				bricks.Remove (name);
		}

		void random_xy (out float x, out float y)
		{
				System.Random random = new System.Random ();
				x = (float)random.NextDouble () * 8.78f - 4.39f;
				y = (float)random.NextDouble () * 7.69f + 2.0f;
		}
	
		public void spawnBrick ()
		{
				float x, y;
				random_xy (out x, out y);
				Instantiate (brickPrefab, new Vector3 (x, y, -.5f), Quaternion.identity);
		}

		public void addScore ()
		{
				score += 10;
				GUI_score.text = "Score: " + score;
		}

		void OnGUI ()
		{
				GUI.skin = mySkin;
				if (GUI.Button (new Rect (0, 50, 100, 50), "RESTART")) {
						Application.LoadLevel (Application.loadedLevel);	
				}
				if (GUI.Button (new Rect (0, 100, 100, 50), "QUIT") || Input.GetKey ("escape")) {
						Application.Quit ();
				}
		}
}
