using UnityEngine;
using System.Collections;

public class brick : MonoBehaviour
{
	 
	static long count;
	public AudioClip myAudio;

		// Use this for initialization
		void Start ()
		{
		gameObject.name	=gameObject.name+count;
		GameObject.Find ("manager").GetComponent<manager> ().populateLevel(gameObject.name);
		count++;
		}
	
		// Update is called once per frame
		void Update ()
		{
				
	
		}



		void OnCollisionEnter ()
		{
				Destroy (gameObject);
				GameObject.Find ("manager").GetComponent<manager> ().addScore ();
				GameObject.Find ("manager").GetComponent<manager> ().removeBrick (gameObject.name);
				AudioSource.PlayClipAtPoint (myAudio, transform.position,.3f);

		}
}
