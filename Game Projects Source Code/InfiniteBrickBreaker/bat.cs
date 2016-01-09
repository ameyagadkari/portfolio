using UnityEngine;
using System.Collections;

public class bat : MonoBehaviour
{
		public GameObject ballprefab;
		GameObject attachedball = null;
		GameObject ball = null;
		GUIText GUI_gameover;
		bool isAlive = true;
		// Use this for initialization
		void Start ()
		{
				GUI_gameover = GameObject.Find ("GUI gameover").GetComponent<GUIText> ();
				
				GameObject.Find ("GUI score").GetComponent<GUIText> ().text = "Score: 0";
				SpawnBall ();
		}

		void SpawnBall ()
		{
				attachedball = (GameObject)Instantiate (ballprefab);
				ball = attachedball;
		}
	
		// Update is called once per frame
		void Update ()
		{
		}

		void FixedUpdate ()
		{
				//Move bat left right
				transform.Translate (10f * Time.deltaTime * Input.GetAxis ("Horizontal"), 0, 0);
				if (transform.position.x > 4.13) {
						transform.position = new Vector3 (4.13f, transform.position.y, transform.position.z);
				} else if (transform.position.x < -4.13) {
						transform.position = new Vector3 (-4.13f, transform.position.y, transform.position.z);
				} 

				//Launch ball using space
				if (attachedball) {
						attachedball.GetComponent<Rigidbody>().position = transform.position + new Vector3 (0, .20f, 0);
						if (Input.GetButtonDown ("Jump")) {
						
								attachedball.GetComponent<Rigidbody>().isKinematic = false;
								attachedball.GetComponent<Rigidbody>().AddForce (300f * Input.GetAxis ("Horizontal"), 300f, 0);
								attachedball = null;
						}

				}
				if (isAlive && ball.GetComponent<Rigidbody>().position.y < -1f) {
						Destroy (ball);
						isAlive = false;
						GUI_gameover.text = "GAME OVER";
						Destroy(gameObject);
			GameObject.Find ("manager").GetComponent<manager> ().diplayHighScore();
				}

		}

		void OnCollisionEnter (Collision col)
		{
				foreach (ContactPoint contact in col.contacts) {
						if (contact.thisCollider == GetComponent<Collider>()) {
								contact.otherCollider.GetComponent<Rigidbody>().AddForce (300f * (contact.point.x - transform.position.x), 0, 0);
						}	
				}
		}
}