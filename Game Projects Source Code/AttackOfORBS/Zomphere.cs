using UnityEngine;
using System.Collections;

public class Zomphere : MonoBehaviour
{
		public AudioClip orb_Destroyed;
		static long count;
		static Generator generator;
		bool isMoving = false;
		int select;
		static Transform sword;
		// Use this for initialization
		void Start ()
		{
				gameObject.name = gameObject.name + count;
				generator = GameObject.Find ("Generator").GetComponent<Generator> ();
				generator.PopulateLevel (gameObject.name);
				count++;
				select = Random.Range (0, 3);
				sword = GameObject.Find ("Sword").GetComponent<Transform> ();
		}
	
		// Update is called once per frame
		void Update ()
		{

				if (transform.position == GameObject.Find ("Main Camera").transform.position) {
						generator.RemoveSphere (gameObject.name);
						GameObject.Find ("Sword").GetComponent<Sword> ().miss ();
						Destroy (gameObject);
				}
	
		}

		void FixedUpdate ()
		{
				StartCoroutine (ChangeColor ());
				if (isMoving) {
						StartCoroutine (MoveSphere ());
				}
				CollisionDetect ();

		}

		void CollisionDetect ()
		{
				if ((transform.position.x >= (sword.position.x - 1f) & transform.position.x <= (sword.position.x + 1f)) && (transform.position.y >= (sword.position.y - 1f) & transform.position.y <= (sword.position.y + 1f)) && (transform.position.z >= (sword.position.z - 1f) & transform.position.z <= (sword.position.z + 1f))) {
						if (ModeSelect.chooseScript) {
				
								if ((select == 0 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.red) | (select == 1 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.green) | (select == 2 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.blue)) {
										generator.RemoveSphere (gameObject.name);
										GameObject.Find ("Sword").GetComponent<Sword> ().hit ();
										switch (select) {
										case 0:
												Instantiate (generator.red, transform.position, Quaternion.identity);
												break;
										case 1:
												Instantiate (generator.green, transform.position, Quaternion.identity);
												break;
										case 2:
												Instantiate (generator.blue, transform.position, Quaternion.identity);
												break;
										}
										AudioSource.PlayClipAtPoint (orb_Destroyed, transform.position);
										Destroy (gameObject);
					
								}
						} else {
				
								if ((select == 0 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.yellow) | (select == 1 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.cyan) | (select == 2 & GameObject.Find ("Sword").GetComponent<Renderer> ().material.color == Color.magenta)) {
										generator.RemoveSphere (gameObject.name);
										GameObject.Find ("Sword").GetComponent<Sword> ().hit ();
										switch (select) {
										case 0:
												Instantiate (generator.yellow, transform.position, Quaternion.identity);
												break;
										case 1:
												Instantiate (generator.cyan, transform.position, Quaternion.identity);
												break;
										case 2:
												Instantiate (generator.magenta, transform.position, Quaternion.identity);
												break;
										}
										AudioSource.PlayClipAtPoint (orb_Destroyed, transform.position);
										Destroy (gameObject);	
								}
	
						}
				}
				
		}
	
		IEnumerator ChangeColor ()
		{
				if (ModeSelect.chooseScript) {
						switch (select) {
						case 0:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.red;
								break;
						case 1:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.green;
								break;
						case 2:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.blue;
								break;
						}
				} else {
						switch (select) {
						case 0:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.red;
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.green;
								break;
						case 1:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.green;
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.blue;
								break;
						case 2:	
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.blue;
								yield return new WaitForSeconds (1);
								gameObject.GetComponent<Renderer>().material.color = Color.red;
								break;
						}

				}
				isMoving = true;

		}

		IEnumerator MoveSphere ()
		{
				yield return new WaitForSeconds (1);
				transform.position = Vector3.MoveTowards (transform.position, GameObject.Find ("Main Camera").transform.position, 25f * Time.deltaTime);


		}
}