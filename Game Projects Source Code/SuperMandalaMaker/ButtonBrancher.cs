using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;

public class ButtonBrancher : MonoBehaviour {
    public class ButtonScaler
    {
        enum ScaleMode { MatchWidhtHeight, IndependentWidthHeight }
        ScaleMode scaleMode;
        Vector2 referenceButtonSize;
        [HideInInspector]
        public Vector2 referenceScreenSize;
        public Vector2 newButtonSize;
        public void Initialize(Vector2 referenceButtonSize, Vector2 referenceScreenSize, int scaleMode)
        {
            this.referenceButtonSize = referenceButtonSize;
            this.referenceScreenSize = referenceScreenSize;
            this.scaleMode = (ScaleMode)scaleMode;
            SetNewButtonSize();
        }
        void SetNewButtonSize()
        {
            if(scaleMode==ScaleMode.IndependentWidthHeight)
            {
                newButtonSize.x = (referenceButtonSize.x * Screen.width) / referenceScreenSize.x;
                newButtonSize.y = (referenceButtonSize.y * Screen.height) / referenceScreenSize.y;
            }
            else
            {
                newButtonSize.x = newButtonSize.y = (referenceButtonSize.x * Screen.width) / referenceScreenSize.x;
            }
        }
    }
    [System.Serializable]
    public class RevealSettings
    {
        public enum RevealOption { Linear, Circular }
        public RevealOption revealOption;
        public float translateSmooth = 5f;
        public float fadeSmooth = 0.01f;
        public bool revealOnStart = false;

        [HideInInspector]
        public bool opening = false;
        [HideInInspector]
        public bool spawned = false;
    }
    [System.Serializable]
    public class LinearSpawner
    {
        public enum RevealStyle { SlideToPosition, FadeInAtPosition }
        public RevealStyle revealStyle;
        public Vector2 direction = new Vector2(0, 1);
        public float baseButtonSpacing = 5f;
        public int buttonNumberOffeset = 0;

        [HideInInspector]
        public float buttonSpacing = 0;

        public void FitSpacingToScreenSize(Vector2 referenceScreenSize)
        {
            float referenceScreenFloat = (referenceScreenSize.x + referenceScreenSize.y) / 2;
            float screenFloat = (Screen.width + Screen.height) / 2;
            buttonSpacing = (baseButtonSpacing * screenFloat) / referenceScreenFloat;
        }
    }
    [System.Serializable]
    public class CircularSpawner
    {
        public enum RevealStyle { SlideToPosition, FadeInAtPosition }
        public RevealStyle revealStyle;
        public Angle angle;
        public float baseDistanceFromBrancher = 20;

        [HideInInspector]
        public float distanceFromBrancher = 0;

        [System.Serializable]
        public struct Angle { public float minAngle; public float maxAngle; }
        public void FitDistanceToScreenSize(Vector2 referenceScreenSize)
        {
            float referenceScreenFloat = (referenceScreenSize.x + referenceScreenSize.y) / 2;
            float screenFloat = (Screen.width + Screen.height) / 2;
            distanceFromBrancher = (baseDistanceFromBrancher * screenFloat) / referenceScreenFloat;
        }
    }

    public GameObject[] buttonReferences;
    [HideInInspector]
    public List<GameObject> buttons;

    public enum ScaleMode { MatchWidhtHeight, IndependentWidthHeight }
    public ScaleMode scaleMode;
    public Vector2 referenceButtonSize;
    public Vector2 referenceScreenSize;

    ButtonScaler buttonScaler = new ButtonScaler();
    public RevealSettings revealSettings = new RevealSettings();
    public LinearSpawner linearSpawner = new LinearSpawner();
    public CircularSpawner circularSpawner = new CircularSpawner();

    float lastScreenWidth = 0;
    float lastScreenHeight = 0;

    void Start()
    {
        buttons = new List<GameObject>();
        buttonScaler = new ButtonScaler();
        lastScreenWidth = Screen.width;
        lastScreenHeight = Screen.height;
        buttonScaler.Initialize(referenceButtonSize, referenceScreenSize, (int)scaleMode);
        circularSpawner.FitDistanceToScreenSize(buttonScaler.referenceScreenSize);
        linearSpawner.FitSpacingToScreenSize(buttonScaler.referenceScreenSize);
    }
    void Update()
    {
        if(Screen.width!=lastScreenWidth || Screen.height!=lastScreenHeight)
        {
            lastScreenWidth = Screen.width;
            lastScreenHeight = Screen.height;
            buttonScaler.Initialize(referenceButtonSize, referenceScreenSize, (int)scaleMode);
            circularSpawner.FitDistanceToScreenSize(buttonScaler.referenceScreenSize);
            linearSpawner.FitSpacingToScreenSize(buttonScaler.referenceScreenSize);
            SpawnButtons();
        }
        if(revealSettings.opening)
        {
            if(!revealSettings.spawned)
            {
                SpawnButtons();
            }

            switch (revealSettings.revealOption)
            {
                case RevealSettings.RevealOption.Linear:
                    switch (linearSpawner.revealStyle)
                    {
                        case LinearSpawner.RevealStyle.SlideToPosition: RevealLinearlyNormal(); break;
                        case LinearSpawner.RevealStyle.FadeInAtPosition: RevealLinearlyFade(); break;
                    }
                    break;
                case RevealSettings.RevealOption.Circular:
                    switch (circularSpawner.revealStyle)
                    {
                        case CircularSpawner.RevealStyle.SlideToPosition: RevealCircularNormal(); break;
                        case CircularSpawner.RevealStyle.FadeInAtPosition: RevealCircularFade(); break;
                    }
                    break;
            }
        }
    }
    public void Create_Destroy()
    {
        if (!revealSettings.opening)
        {
            revealSettings.opening = true;
            for (int i = 0; i < buttons.Count; i++)
            {
                Destroy(buttons[i]);
            }
            buttons.Clear();
            ClearCommonButtonBranchers();
            SpawnButtons();
        }
        else
        {
            for (int i = 0; i < buttons.Count; i++)
            {
                Destroy(buttons[i]);
            }
            buttons.Clear();
            revealSettings.opening = false;
            revealSettings.spawned = false;
        }
    }
    void SpawnButtons()
    { 
        for (int i = 0; i < buttonReferences.Length; i++)
        {
            GameObject button = Instantiate(buttonReferences[i] as GameObject);
            button.transform.SetParent(transform);
            button.transform.position = transform.position;
            if (linearSpawner.revealStyle == LinearSpawner.RevealStyle.FadeInAtPosition || circularSpawner.revealStyle == CircularSpawner.RevealStyle.FadeInAtPosition)
            {
                Color color = button.GetComponent<Image>().color;
                color.a = 0;
                button.GetComponent<Image>().color = color;
                if (button.GetComponent<Text>())
                {
                    color = button.GetComponent<Text>().color;
                    color.a = 0;
                    button.GetComponent<Text>().color = color;
                }
            }
            buttons.Add(button);
        }
        revealSettings.spawned = true;
    }
    void RevealLinearlyNormal()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            Vector3 targetPosition;
            RectTransform buttonRectangle = buttons[i].GetComponent<RectTransform>();
            buttonRectangle.sizeDelta = new Vector2(buttonScaler.newButtonSize.x, buttonScaler.newButtonSize.y);
            targetPosition.x = linearSpawner.direction.x * ((i + linearSpawner.buttonNumberOffeset) * (buttonRectangle.sizeDelta.x + linearSpawner.buttonSpacing)) + transform.position.x;
            targetPosition.y = linearSpawner.direction.y * ((i + linearSpawner.buttonNumberOffeset) * (buttonRectangle.sizeDelta.y + linearSpawner.buttonSpacing)) + transform.position.y;
            targetPosition.z = 0;

            buttonRectangle.position = Vector3.Lerp(buttonRectangle.position, targetPosition, revealSettings.translateSmooth * Time.deltaTime);
        }
    }
    void RevealLinearlyFade()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            Vector3 targetPosition;
            RectTransform buttonRectangle = buttons[i].GetComponent<RectTransform>();
            buttonRectangle.sizeDelta = new Vector2(buttonScaler.newButtonSize.x, buttonScaler.newButtonSize.y);
            targetPosition.x = linearSpawner.direction.x * ((i + linearSpawner.buttonNumberOffeset) * (buttonRectangle.sizeDelta.x + linearSpawner.buttonSpacing)) + transform.position.x;
            targetPosition.y = linearSpawner.direction.y * ((i + linearSpawner.buttonNumberOffeset) * (buttonRectangle.sizeDelta.y + linearSpawner.buttonSpacing)) + transform.position.y;
            targetPosition.z = 0;

            ButtonFader previousButtonFader;
            if (i > 0)
            {
                previousButtonFader = buttons[i - 1].GetComponent<ButtonFader>();
            }
            else
            {
                previousButtonFader = null;
            }
            ButtonFader buttonFader = buttons[i].GetComponent<ButtonFader>();
            if(previousButtonFader)
            {
                if(previousButtonFader.faded)
                {
                    buttons[i].transform.position = targetPosition;
                    if(buttonFader)
                    {
                        buttonFader.Fade(revealSettings.fadeSmooth);
                    }
                    else
                    {
                        Debug.LogError("You want to fade your buttons, but they need a ButtonFader script to be attached  first");
                    }
                }
            }
            else
            {
                buttons[i].transform.position = targetPosition;
                if (buttonFader)
                {
                    buttonFader.Fade(revealSettings.fadeSmooth);
                }
                else
                {
                    Debug.LogError("You want to fade your buttons, but they need a ButtonFader script to be attached  first");
                }
            }
        }
    }
    void RevealCircularNormal()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            float angleDistance = circularSpawner.angle.maxAngle - circularSpawner.angle.minAngle;
            float targetAngle = circularSpawner.angle.minAngle + (angleDistance / buttons.Count) * i;
            Vector3 targetPosition = transform.position + Vector3.right * circularSpawner.distanceFromBrancher;
            targetPosition = RotateAroundPivot(targetPosition, transform.position, targetAngle);
            RectTransform buttonRectangle = buttons[i].GetComponent<RectTransform>();
            buttonRectangle.sizeDelta = new Vector2(buttonScaler.newButtonSize.x, buttonScaler.newButtonSize.y);
            buttonRectangle.position = Vector3.Lerp(buttonRectangle.position, targetPosition, revealSettings.translateSmooth * Time.deltaTime);
        }
    }
    void RevealCircularFade()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            float angleDistance = circularSpawner.angle.maxAngle - circularSpawner.angle.minAngle;
            float targetAngle = circularSpawner.angle.minAngle + (angleDistance / buttons.Count) * i;
            Vector3 targetPosition = transform.position + Vector3.right * circularSpawner.distanceFromBrancher;
            targetPosition = RotateAroundPivot(targetPosition, transform.position, targetAngle);
            RectTransform buttonRectangle = buttons[i].GetComponent<RectTransform>();
            buttonRectangle.sizeDelta = new Vector2(buttonScaler.newButtonSize.x, buttonScaler.newButtonSize.y);

            ButtonFader previousButtonFader;
            if (i > 0)
            {
                previousButtonFader = buttons[i - 1].GetComponent<ButtonFader>();
            }
            else
            {
                previousButtonFader = null;
            }
            ButtonFader buttonFader = buttons[i].GetComponent<ButtonFader>();
            if (previousButtonFader)
            {
                if (previousButtonFader.faded)
                {
                    buttons[i].transform.position = targetPosition;
                    if (buttonFader)
                    {
                        buttonFader.Fade(revealSettings.fadeSmooth);
                    }
                    else
                    {
                        Debug.LogError("You want to fade your buttons, but they need a ButtonFader script to be attached  first");
                    }
                }
            }
            else
            {
                buttons[i].transform.position = targetPosition;
                if (buttonFader)
                {
                    buttonFader.Fade(revealSettings.fadeSmooth);
                }
                else
                {
                    Debug.LogError("You want to fade your buttons, but they need a ButtonFader script to be attached  first");
                }
            }
        }
    }

    Vector3 RotateAroundPivot(Vector3 point, Vector3 pivot,float angle)
    {
        Vector3 targetPoint = point - pivot;
        targetPoint = Quaternion.Euler(0, 0, angle) * targetPoint;
        targetPoint += pivot;
        return targetPoint;
    }
    void ClearCommonButtonBranchers()
    {
        GameObject[] branchers = GameObject.FindGameObjectsWithTag("ButtonBrancher");
        foreach (GameObject brancher in branchers)
        {
            if (brancher.transform.parent == transform.parent)
            {
                ButtonBrancher buttonBranchers = brancher.GetComponent<ButtonBrancher>();
                for (int i = 0; i < buttonBranchers.buttons.Count; i++)
                {
                    Destroy(buttonBranchers.buttons[i]);
                }
                buttonBranchers.buttons.Clear();
                if (buttonBranchers.revealSettings.opening && buttonBranchers.revealSettings.spawned)
                {
                    buttonBranchers.revealSettings.opening = false;
                }
            }
        }
        revealSettings.opening = true;
    }
}
