using UnityEngine;
using System.Collections;

public class Generator : MonoBehaviour
{
		public GameObject spherePrefab, red, green, blue, yellow, cyan, magenta;
		ArrayList sphere = new ArrayList ();
		bool isSpawning = false;
		// Use this for initialization
		void Start ()
		{
		
		}
		// Update is called once per frame
		void Update ()
		{
	
		}

		void FixedUpdate ()
		{
				if (sphere.Count < 25 && ! isSpawning) {
						isSpawning = true; 
						StartCoroutine (SpawnSphere ());
				}
		}

		public void PopulateLevel (string name)
		{
				sphere.Add (name);
		}

		public void RemoveSphere (string name)
		{
				sphere.Remove (name);
		}

		IEnumerator SpawnSphere ()
		{
				Instantiate (spherePrefab, new Vector3 (Random.Range (transform.position.x - 50f, transform.position.x + 50f), 5f, Random.Range (transform.position.z - 15f, transform.position.z + 15f)), Quaternion.identity);
				yield return new WaitForSeconds (1);
				isSpawning = false;
		}
}
