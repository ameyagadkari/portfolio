using UnityEngine;
using System.Collections;

public class ModeSelect : MonoBehaviour {

	// Use this for initialization
	public static bool chooseScript;
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
	}
	void Awake () {
		DontDestroyOnLoad (gameObject);
	}
}
