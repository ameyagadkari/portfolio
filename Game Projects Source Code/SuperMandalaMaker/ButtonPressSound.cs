using UnityEngine;
using System.Collections;

public class ButtonPressSound : MonoBehaviour {
    AudioSource buttonPressSound;
    void Start()
    {
        buttonPressSound = GameObject.Find("Button Press Sound").GetComponent<AudioSource>();
    }
    public void PlayButtonPressSound()
    {
        buttonPressSound.PlayOneShot(buttonPressSound.clip);
    }
}
