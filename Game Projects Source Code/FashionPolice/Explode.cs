using UnityEngine;
using System.Collections;

public class Explode : MonoBehaviour {

    GameObject explosion;
    
    void Start () {
        explosion = Resources.Load("explosion") as GameObject;
    }
	
	void Update () {
	
	}

    void OnCollisionEnter(Collision collision)
    {
        GameObject explode = Instantiate(explosion,transform.position,transform.rotation) as GameObject;
        Destroy(this.gameObject);
    }
}
