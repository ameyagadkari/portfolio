using UnityEngine;
using System.Collections;

public class DirectionalLight : MonoBehaviour {
	public GUISkin mySkin;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	void OnGUI(){
		GUI.skin = mySkin;
		if (GUI.Button (new Rect (Screen.width-200, 0, 200, 50), "BACK TO MAIN MENU")||Input.GetKeyDown("escape")) {
			Application.LoadLevel (0);	
		}
	}
}
