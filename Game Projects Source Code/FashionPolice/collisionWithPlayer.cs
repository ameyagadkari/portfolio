using UnityEngine;
using System.Collections;

public class collisionWithPlayer : MonoBehaviour {
    public movement move;
    void OnCollisionEnter(Collision collision)
    {
        ContactPoint contact = collision.contacts[0];
        if (collision.gameObject.name=="FashionPolice")
        {
            move = collision.gameObject.GetComponent("movement") as movement;
            move.speed = 0.0f;
            collision.gameObject.transform.RotateAround(contact.point, Vector3.up, 20*Time.deltaTime);
        }
    }

    // Use this for initialization
    void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
