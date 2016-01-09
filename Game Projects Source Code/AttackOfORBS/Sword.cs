using UnityEngine;
using System.Collections;

public class Sword : MonoBehaviour
{
		static int select;
		int health;
		float highscore, myscore;
		GUIText health_text, time_text;
		// Use this for initialization
		void Start ()
		{
				health_text = GameObject.Find ("Health").GetComponent<GUIText> ();
				time_text = GameObject.Find ("Time").GetComponent<GUIText> ();
				health = 10;
				myscore = 0;
				health_text.text = "Health: " + health;
				time_text.text = "Time: " + myscore.ToString ("f1") + " secs";
				if (ModeSelect.chooseScript) {
						highscore = PlayerPrefs.GetFloat ("HighestTimeSurvied_n");
						gameObject.GetComponent<Renderer>().material.color = Color.red;
				} else {
						highscore = PlayerPrefs.GetFloat ("HighestTimeSurvied_i");
						gameObject.GetComponent<Renderer>().material.color = Color.yellow;
				}
				select = 1;
		}
	
		// Update is called once per frame
		void Update ()
		{
				myscore += Time.deltaTime;
				if (Input.GetButtonDown ("Fire1")) {
						if (ModeSelect.chooseScript) {
								switch (select) {
								case 0:
										gameObject.GetComponent<Renderer>().material.color = Color.red;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.red;
										select = 1;
										break;
								case 1:
										gameObject.GetComponent<Renderer>().material.color = Color.green;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.green;
										select = 2;
										break;
								case 2:
										gameObject.GetComponent<Renderer>().material.color = Color.blue;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.blue;
										select = 0;
										break;
								}

						} else {
								switch (select) {
								case 0:
										gameObject.GetComponent<Renderer>().material.color = Color.yellow;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.yellow;
										select = 1;
										break;
								case 1:
										gameObject.GetComponent<Renderer>().material.color = Color.cyan;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.cyan;
										select = 2;
										break;
								case 2:
										gameObject.GetComponent<Renderer>().material.color = Color.magenta;
										GameObject.Find ("Illuminator").GetComponent<Light> ().color = Color.magenta;
										select = 0;
										break;
								}

						}
						
				}
				if (health <= 0) {
						if (myscore > highscore) {
								if (ModeSelect.chooseScript) {
										PlayerPrefs.SetFloat ("HighestTimeSurvied_n", myscore);

								} else {
										PlayerPrefs.SetFloat ("HighestTimeSurvied_i", myscore);
								}
								
						}
						PlayerPrefs.SetFloat ("TimeSurvied", myscore);
						Application.LoadLevel (2);
	
				}
				time_text.text = "Time: " + myscore.ToString ("f1") + " secs";
		}

		public void hit ()
		{
				health++;
				health_text.text = "Health: " + health;
		}

		public void miss ()
		{
				health -= 2;
				health_text.text = "Health: " + health;
		}
}