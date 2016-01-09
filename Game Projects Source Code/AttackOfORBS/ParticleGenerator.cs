using UnityEngine;
using System.Collections;

public class ParticleGenerator : MonoBehaviour
{
		// Use this for initialization
		void Start ()
		{
		}


	
		// Update is called once per frame
		void Update ()
		{
				if (!gameObject.GetComponent<ParticleSystem>().isPlaying) {
						Destroy (gameObject);
				}
		}
}