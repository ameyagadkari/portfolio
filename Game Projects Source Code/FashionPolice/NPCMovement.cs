using UnityEngine;
using System.Collections;

public class NPCMovement : MonoBehaviour {
    [Range(1, 10)]
    public float moveSpeed;
    [Range(1, 100)]
    public float rotateSpeed;
    public GameObject[] points;
    int pointNumber;
    bool isRotating;
    bool isMoving;
    void Start()
    {
        isMoving = true;
        pointNumber = 0;
        isRotating = false;
    }
    void Update()
    {
        if(isMoving)
        {
            if (isRotating)
            {
                if (transform.rotation == points[pointNumber].transform.rotation)
                {
                    isRotating = false;
                    if (pointNumber == 3)
                    {
                        pointNumber = 0;
                    }
                    else
                    {
                        pointNumber++;
                    }
                }
                else
                {
                    transform.rotation = Quaternion.RotateTowards(transform.rotation, points[pointNumber].transform.rotation, rotateSpeed * Time.deltaTime);
                }
            }
            else
            {
                if (transform.position == points[pointNumber].transform.position)
                {
                    isRotating = true;
                }
                else
                {
                    transform.position = Vector3.MoveTowards(transform.position, points[pointNumber].transform.position, moveSpeed * Time.deltaTime);
                }
            }
        }   
    }
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "FashionPolice")
        {
            isMoving = false;
        }
    }
}
