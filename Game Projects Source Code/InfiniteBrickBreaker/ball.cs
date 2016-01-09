using UnityEngine;
using System.Collections;

public class ball : MonoBehaviour {
	public AudioClip[] myAudio;
	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
	}
	void OnCollisionEnter (){
		AudioSource.PlayClipAtPoint (myAudio[Random.Range (0, myAudio.Length)], transform.position,.25f);
	}
}
