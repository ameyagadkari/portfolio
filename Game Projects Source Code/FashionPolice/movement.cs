using UnityEngine;
using System.Collections;

public class movement : MonoBehaviour
{
    [SerializeField]
    [Range(1, 20)]

    public float speed = 2.6f;
    private Vector3 targetPosition;
    private bool isMoving;
    public Camera playerCamera;
    public float player_rot_angle;

    const int LEFT_MOUSE_BUTTON = 0;
    //Accelerometer
    public bool isCalibrated;
    private float avg_y_accel;
    private float avg_y_accel_temp;
    private float calib_count;

    public bool canMove = true;
    void Start()
    {
        targetPosition = transform.position;
        isMoving = false;

        //Accel
        isCalibrated = false;
        avg_y_accel = 0;
        calib_count = 0;
    }

    void Update()
    {
        //if (Input.GetMouseButton(LEFT_MOUSE_BUTTON))
        //    SetTargetPosition();

        //if (isMoving)
        //    MovePlayer();

        if (calib_count == 100 || SystemInfo.deviceType == DeviceType.Desktop)
        {
            avg_y_accel_temp = avg_y_accel;
            avg_y_accel_temp /= calib_count;
            isCalibrated = true;
        }

        if (!isCalibrated)
        {
            avg_y_accel += Input.acceleration.y;
            calib_count++;
        }

        if (Input.GetKey(KeyCode.W) || isCalibrated == true && Input.acceleration.y > 0.2 + avg_y_accel_temp)
        {
            if(canMove)
            MovePlayer();
        }

        if (Input.GetKey(KeyCode.A) || isCalibrated == true && Input.acceleration.x < 0)
        {
            transform.Rotate(Vector3.down, player_rot_angle);
        }
        if (Input.GetKey(KeyCode.D) || isCalibrated == true && Input.acceleration.x > 0.2)
        {
            transform.Rotate(Vector3.up, player_rot_angle);
        }
    }


    //void SetTargetPosition()
    //{
    //    speed = 2.6f;
    //    //Plane plane = GameObject.Find("room").transform.Find("floor");
    //    Plane plane = new Plane(Vector3.up, transform.position);
    //    Ray ray = playerCamera.ScreenPointToRay(Input.mousePosition);

    //    float point = 0f;

    //    if (plane.Raycast(ray, out point))
    //        targetPosition = ray.GetPoint(point);

    //    isMoving = true;
    //}

    void MovePlayer()
    {
        //transform.LookAt(targetPosition);
        //transform.position = Vector3.MoveTowards(transform.position, targetPosition, speed * Time.deltaTime);
        //targetPosition = new Vector3(transform.position.x + 10, transform.position.y , transform.position.z + 10);
        //transform.position = Vector3.MoveTowards(transform.position, targetPosition, speed * Time.deltaTime);
        transform.Translate(Vector3.forward * Time.deltaTime * 4);


        if (transform.position == targetPosition)
            isMoving = false;
    }

    void OnGUI()
    {
        //GUI.Label(new Rect(0, 0, 200, 200), Input.acceleration.x.ToString());
        //GUI.Label(new Rect(0, 20, 200, 200), Input.acceleration.y.ToString());
        //GUI.Label(new Rect(0, 40, 200, 200), Input.acceleration.z.ToString());



        if (!isCalibrated)
        {
            GUIStyle calib_text_style = new GUIStyle();
            calib_text_style.fontSize += 50;
            calib_text_style.normal.textColor = Color.white;
            calib_text_style.alignment = TextAnchor.UpperCenter;
            //GUI.Label(new Rect(Screen.width / 2 - 50, Screen.height / 2 - 50, 100, 50), "Hold phone still for calibration", calib_text_style);
        }
        else
        {
            //GUI.Label(new Rect(0, 100, 200, 200), avg_y_accel.ToString());
            //GUI.Label(new Rect(0, 120, 200, 200), avg_y_accel_temp.ToString());
        }


    }
}