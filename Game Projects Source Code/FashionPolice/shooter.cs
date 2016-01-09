using UnityEngine;
using System.Collections;

public class shooter : MonoBehaviour {

    GameObject glamBullet;
    public Camera bulletCamera;
    int damping = 1;
    Vector3 Target;
    public int count = 0;

    //Shooting fix
    bool canFire;
    void Start () {
        glamBullet = Resources.Load("glamBullet") as GameObject;
        canFire = true;
    }
	
	void Update () {
	    if(Input.GetMouseButtonDown(0) && (canFire))
        {
            Transform cur_trans = GetComponent<Transform>();
                 
            Target = bulletCamera.ScreenToWorldPoint(Input.mousePosition);
           
            //Debug.Log(Target);
            //Vector3 lookPos = (Target - cur_trans.parent.position);
            //lookPos.y = 0;
            //Quaternion gunRotation = Quaternion.LookRotation(lookPos);
            //cur_trans.rotation = Quaternion.Slerp(cur_trans.rotation,gunRotation,Time.deltaTime);

            Ray ray = bulletCamera.ScreenPointToRay(Input.mousePosition);
           // Debug.Log(ray.GetPoint(100));
            cur_trans.LookAt(ray.GetPoint(10), Vector3.up);
            Transform temp_trans = cur_trans;

            cur_trans.Rotate(0, 90, 0);
            count++;

            GameObject bullet = Instantiate(glamBullet) as GameObject;
            bullet.transform.position = transform.position ;
            Rigidbody rb = bullet.GetComponent<Rigidbody>();
            rb.velocity = temp_trans.transform.right * -20;
        }
	}

    public void setFire(bool i_canFire)
    {
        canFire = i_canFire;
    }

}
