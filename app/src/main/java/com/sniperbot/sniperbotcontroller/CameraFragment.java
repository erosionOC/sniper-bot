/**
 * Fragment to contain video feed
 */

package com.sniperbot.sniperbotcontroller;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;



public class CameraFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_camera,
                container, false);
        return view;
    }


    /**
     * Just here as a placeholder
     */
    public void setText(String item) {
        TextView view = (TextView) getView().findViewById(R.id.cameraText);
        view.setText(item);
    }
}
